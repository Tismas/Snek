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
		Segment(int x, int y) : x(x), y(y) {}

		int x, y;
		bool operator==(const Segment& rv) const{ return x == rv.x && y == rv.y; }
		bool operator==(const Obstacle& rv) const { return x == rv.x && y == rv.y; }
	};
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColors[] = { {0,200,40}, {0,100,20} };
	
	float x, y, speed;
	std::deque<Segment> segments;
	direction dir;
	unsigned char controls[4];
public:
	Snake(int x = 5, int y = 5, direction dir = up, const unsigned char controls[] = NULL);
	~Snake();

	void draw(Board& board) const;
	void update(const Board& board, const Keyboard& kbd, Apple& apple, float dt, std::vector<Obstacle>& obstacles);
	bool deathCheck(const std::vector<Obstacle>& obstacles, const std::vector<Snake>& sneks) const;
	void reset(int x, int y);
};

