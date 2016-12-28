#include "Apple.h"

#include <random>

std::vector<Color> Apple::colors({Colors::Red, Colors::Blue, Colors::Cyan, Colors::Green});

Apple::Apple(int x, int y): x(x), y(y) {
}


Apple::~Apple() {
}

void Apple::draw(Board & board) const {
	board.drawCell(x, y, colors[type]);
}

void Apple::setPos(int x, int y) {
	this->x = x;
	this->y = y;
}

void Apple::reposition(const Board& board) {
	std::uniform_int_distribution<int> xDist(0, board.getWidth()-1);
	std::uniform_int_distribution<int> yDist(0, board.getHeight()-1);
	std::random_device rd;
	std::mt19937 rng(rd());
	setPos(xDist(rng), yDist(rng));

	std::uniform_int_distribution<int> typeDist(0, (int)colors.size() - 1);
	type = typeDist(rng);
}
