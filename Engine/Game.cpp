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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	apple(10,10)
{
	apple.reposition(board, obstacles);
	dt = 0;
	last = std::chrono::steady_clock::now();
	unsigned char controls[4][4] = { { VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT }, { 'W', 'D', 'S', 'A' } };
	sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, up, controls[0]));
	sneks.push_back(Snake(board.getWidth() / 2, board.getHeight() / 2, down, controls[1]));
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel() {
	using namespace std::chrono;
	auto mark = steady_clock::now();
	std::chrono::duration<float> duration = mark - last;
	dt = duration.count();
	last = mark;

	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		gameOver = false;
		obstacles.clear();
		apple.reposition(board, obstacles);
		for(int i=0;i<sneks.size();++i)
			sneks[i].reset(board.getWidth()/2, board.getHeight()/2);
	}

	if (gameOver) return;

	for (int i = 0; i < sneks.size(); ++i) {
		sneks[i].update(board, wnd.kbd, apple, dt, obstacles);
		if (sneks[i].deathCheck(obstacles, sneks)) {
			gameOver = true;
		}
	}
}

void Game::ComposeFrame() {
	if (gameOver) return;
	board.drawBorder();
	apple.draw(board);
	for (int i = 0; i < sneks.size(); ++i)
		sneks[i].draw(board);
	for (int i = 0; i < obstacles.size(); i++)
		obstacles[i].draw(board);
}
