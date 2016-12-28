#include "Apple.h"

#include <random>

std::vector<Color> Apple::colors({ { 95,27,135 }, { 215, 143, 63 }, { 87, 147, 247 }, { 39, 195, 39 }, { 247, 211, 55 }, { 215, 15, 31} });

Apple::Apple(int x, int y): x(x), y(y) {
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

void Apple::reposition(const Board& board, const std::vector<Obstacle>& obstacles) {
	std::random_device rd;
	std::mt19937 rng(rd());

	bool intersects = false;
	do {
		std::uniform_int_distribution<int> xDist(0, board.getWidth() - 1);
		std::uniform_int_distribution<int> yDist(0, board.getHeight() - 1);
		setPos(xDist(rng), yDist(rng));

		for (int i = 0; i < obstacles.size(); i++) {
			if (obstacles[i].x == x && obstacles[i].y == y) intersects = true;
		}
	} while (intersects);

	std::uniform_int_distribution<int> typeDist(0, (int)colors.size() - 1);
	type = typeDist(rng);
}
