#pragma once

#include <deque>

#include "Colors.h"
#include "Board.h"
#include "Keyboard.h"
#include "Obstacle.h"
#include "Apple.h"

enum direction {
	left, up, right, down
};

class Snake {
	struct Segment {
		int x, y;
		bool operator==(const Segment& rv) { return x == rv.x && y == rv.y; }
	};
	static constexpr Color headColor = Colors::Blue;
	static constexpr Color bodyColors[] = { {0,40,200}, {0,20,100} };
	float x, y, speed;
	std::deque<Segment> segments;
	direction dir = up;
public:
	Snake(float x = 5, float y = 5);
	~Snake();

	void draw(Board& board) const;
	void update(const Board& board, const Keyboard& kbd, Apple& apple, float dt, std::vector<Obstacle>& obstacles);
};

