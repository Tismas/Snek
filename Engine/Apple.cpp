#include "Apple.h"
#include "Snake.h"

#include <random>

std::vector<Color> Apple::colors({
	{ 95,27,135 },		// violet
	{ 215, 143, 63 },	// orange
	{ 87, 147, 247 },	// blue
	{ 39, 195, 39 },	// green
	{ 247, 211, 55 },	// yellow
	{ 215, 15, 31} });	// red

void Apple::initType() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> typeDist(0, (int)colors.size() - 1);
	type = typeDist(rng);
}

Apple::Apple(int x, int y) : x(x), y(y) {
	initType();
}

Apple::Apple(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles) {
	reposition(board, sneks, obstacles);
}


Apple::~Apple() {
}

void Apple::draw(Board & board) const {
	board.drawCircle(x, y, colors[type]);
}

void Apple::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

void Apple::reposition(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles) {
	std::random_device rd;
	std::mt19937 rng(rd());

	bool canSpawn = true;
	do {
		canSpawn = true;
		std::uniform_int_distribution<int> xDist(0, board.getWidth() - 1);
		std::uniform_int_distribution<int> yDist(0, board.getHeight() - 1);
		setPos(xDist(rng), yDist(rng));

		for (int i = 0; i < obstacles.size(); ++i) {
			if (obstacles[i].x == x && obstacles[i].y == y) {
				canSpawn = false;
				break;
			}
		}
		for (int i = 0; i < sneks.size(); ++i) {
			if (sneks[i].isTooClose(*this)) {
				canSpawn = false;
				break;
			}
		}
	} while (!canSpawn);

	initType();
}

void Apple::fireEffect(const Board& board, const std::vector<Snake>& sneks, Snake & snek, std::vector<Obstacle>& obstacles, std::vector<Apple>& apples) {
	if (type == violet) {
		if (obstacles.size()) {
			for (int i = 0; i < 5; ++i) {
				apples.push_back(Apple(obstacles[obstacles.size() - 1].x, obstacles[obstacles.size() - 1].y));
				obstacles.pop_back();
			}
		}
	}
	else if (type == orange) {
	}
	else if (type == blue) {
		// deszcz
	}
	else if (type == green) {
		for (int i = 0; i < 5; ++i)
			apples.push_back(Apple(board, sneks, obstacles));
	}
	else if (type == yellow) {
		for (int i = 0; i < 3 && snek.segments.size(); ++i) {
			snek.segments.pop_back();
		}
	}
	else if (type == red) {
		snek.accelerate();
	}
}
