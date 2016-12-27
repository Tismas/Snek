#pragma once

#include "Colors.h"
#include "Board.h"
#include "Keyboard.h"
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
	static constexpr Color bodyColor = Colors::Cyan;
	static constexpr int maxSegments = 100;
	int nSegments = 0;
	float x, y, speed;
	Segment segments[maxSegments];
	direction dir = up;
public:
	Snake(float x = 5, float y = 5);
	~Snake();

	void draw(Board& board) const;
	void update(const Board& board, const Keyboard& kbd, Apple& apple, float dt);
};

