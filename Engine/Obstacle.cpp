#include "Obstacle.h"

Obstacle::Obstacle(int x, int y) {
	this->x = x;
	this->y = y;
}


Obstacle::~Obstacle() {
}

void Obstacle::draw(Board& board) {
	board.drawCell(x, y, c);
}
