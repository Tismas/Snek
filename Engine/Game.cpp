/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx)
{
	wnd.initPad();
	init();
}

void Game::init() {
	apples.clear();
	deadSneks.clear();
	obstacles.clear();
	sneks.clear();
	dt = 0;

	last = std::chrono::steady_clock::now();
	lastAppleSpawn = std::chrono::steady_clock::now();

	unsigned char controls[4][4] = { { VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT },{ 'W', 'D', 'S', 'A' } };
	sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, up, controls[0], { 20,200,20 }));
	sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, down, controls[1], { 200,20,20 }));
	// sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, left, controls[2], { 20,20,200 }, true, 0));
	// sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, right, controls[2], { 10,150,150 }, true, 1));

	for (int i = 0; i < sneks.size(); ++i) {
		comboCounters.push_back(UICombo(sneks[i], i));
	}
	for (int i = 0; i < 5; i++) {
		apples.push_back(Apple(board, sneks, obstacles));
	}
}

void Game::saveScores() {
	scores.open("scores.txt", std::ios::ate | std::ios::app | std::ios::out);
	sort(deadSneks.begin(), deadSneks.end(), [](const Snake& first, const Snake& second) {return first.score > second.score; });
	for (int i = 0; i < deadSneks.size(); ++i)
		scores << deadSneks[i].color << ": " << deadSneks[i].score << std::endl;
	scores << std::endl;
	scores.close();
}

void Game::Go() {
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel() {
	wnd.pad.Frame();
	using namespace std::chrono;
	auto mark = steady_clock::now();

	std::chrono::duration<float> duration = mark - last;
	dt = duration.count();
	last = mark;
	static int frames = 0;
	if (frames > 60 && wnd.kbd.KeyIsPressed('P')) {
		paused = !paused;
		frames = 0;

	}
	frames++;
	if (paused) return;

	std::chrono::duration<float> timeSinceLastAppleSpawn = mark - lastAppleSpawn;
	if (apples.size() < minApples || apples.size() < maxApples && timeSinceLastAppleSpawn.count() >= 5.0f) {
		apples.push_back(Apple(board, sneks, obstacles));
		lastAppleSpawn = mark;
	}

	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		gameOver = false;
		obstacles.clear();

		for (int i = 0; i < apples.size(); ++i)
			apples[i].reposition(board, sneks, obstacles);
		for (int i = 0; i < sneks.size(); ++i)
			sneks[i].reset(board.getWidth() / 2, board.getHeight() / 2);
	}

	if (gameOver) return;

	for (int i = 0; i < projectiles.size(); ++i) {
		if (projectiles[i].update(obstacles, apples, board) || projectiles[i].shouldBeDeleted(board)) {
			projectiles[i] = projectiles[projectiles.size() - 1];
			projectiles.pop_back();
		}
	}
	for (int i = 0; i < sneks.size(); ++i) {
		sneks[i].update(board, wnd.kbd, wnd.pad, apples, dt, obstacles, sneks, projectiles);
		if (sneks[i].deathCheck(obstacles, sneks)) {
			deadSneks.push_back(sneks[i]);
			sneks[i] = sneks[sneks.size() - 1];
			sneks.pop_back();
			if (sneks.size() == 1) {
				sneks[0].score += 10;
				deadSneks.push_back(sneks[0]);
				sneks.pop_back();
				saveScores();
				init();
			}
		}
	}
}

void Game::ComposeFrame() {
	board.drawBorder();
	for (int i = 0; i < apples.size(); ++i)
		apples[i].draw(board);
	for (int i = 0; i < obstacles.size(); i++)
		obstacles[i].draw(board);
	for (int i = 0; i < projectiles.size(); ++i)
		projectiles[i].draw(gfx);
	for (int i = 0; i < sneks.size(); ++i)
		sneks[i].draw(board);
	for (int i = 0; i < comboCounters.size(); ++i) {
		comboCounters[i].draw(gfx);
	}
}
