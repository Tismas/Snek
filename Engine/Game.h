/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include <chrono>
#include <fstream>
#include <vector>

#include "Image.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include "Obstacle.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void init();
	void saveScores();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::ofstream scores;
	bool gameOver = false;
	bool paused = false;

	static constexpr int maxApples = 20;
	static constexpr int minApples = 5;
	std::chrono::steady_clock::time_point lastAppleSpawn;
	
	Board board;
	std::vector<Snake> sneks;
	std::vector<Snake> deadSneks;
	std::vector<Obstacle> obstacles;
	std::vector<Apple> apples;
	
	float dt;
	std::chrono::steady_clock::time_point last;
	/********************************/
};