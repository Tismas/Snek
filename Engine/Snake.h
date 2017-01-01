#pragma once

#include <deque>

#include "Colors.h"
#include "Board.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Obstacle.h"
#include "Apple.h"
#include <chrono>

enum direction {
	left, up, right, down, none
};

class Snake {
	struct Segment {
		Segment(int x, int y) : x(x), y(y) {}

		int x, y;
		bool operator==(const Segment& rv) const{ return x == rv.x && y == rv.y; }
		bool operator==(const Obstacle& rv) const { return x == rv.x && y == rv.y; }
	};
	static constexpr Color headColor = Colors::Yellow;
	Color bodyColors[2];
	
	float x, y;
	std::deque<Segment> segments;
	direction dir;
	direction pending = none;
	unsigned char controls[4];
	bool byPad;
	int padInd;

	int lifes = 3;
	float speed = 3.0f;
	int lastAppleEaten = -1;
	int appleCombo = 0;

	bool accelerated = false;
	float accelerationValue = 8.0f;
	std::chrono::steady_clock::time_point accelerationTime;

public:
	std::string color;
	int score = 0;
	Snake(int x = 5, int y = 5, direction dir = up, const unsigned char controls[] = NULL, Color BaseColor = Colors::Green, bool controllerByPad = false, int padInd = 0);
	~Snake();

	void draw(Board& board) const;
	void update(const Board& board, const Keyboard& kbd, const Controller& pad, std::vector<Apple>& apples, float dt, std::vector<Obstacle>& obstacles, const std::vector<Snake>& sneks);
	bool deathCheck(const std::vector<Obstacle>& obstacles, std::vector<Snake>& sneks);
	void reset(int x, int y);
	void accelerate();

	bool isTooClose(const Apple& apple) const;

	friend class Apple;
};

