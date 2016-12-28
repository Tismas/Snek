#pragma once

#include "Colors.h"
#include "Board.h"

class Obstacle {
	int x, y;
	static constexpr Color c = Colors::LightGray;
public:
	Obstacle(int x, int y);
	~Obstacle();

	void draw(Board& board);
};
