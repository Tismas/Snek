#pragma once

#include "Colors.h"
#include "Board.h"

class Obstacle {
	static constexpr Color c = { 175, 171, 175 };
public:
	int x, y;
	Obstacle(int x, int y);
	~Obstacle();

	void draw(Board& board);
};
