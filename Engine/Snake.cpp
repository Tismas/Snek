#include "Snake.h"



Snake::Snake(float x, float y) : x(x), y(y) {
	speed = 2.5f;
}

Snake::~Snake() {
}

void Snake::update(const Board& board, const Keyboard& kbd, Apple& apple, float dt) {
	int lastX = (int)x, lastY = (int)y;

	if (dir == left) x-=speed * dt;
	else if (dir == up) y -= speed * dt;
	else if (dir == right) x += speed * dt;
	else y += speed * dt;

	if (x < 0) x = board.getWidth() - speed;
	if (y < 0) y = board.getHeight() - speed;
	if (x >= board.getWidth()) x = 0;
	if (y >= board.getHeight()) y = 0;

	if (kbd.KeyIsPressed(VK_UP)) {
		dir = up;
	}
	else if (kbd.KeyIsPressed(VK_DOWN)) {
		dir = down;
	}
	else if (kbd.KeyIsPressed(VK_LEFT)) {
		dir = left;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT)) {
		dir = right;
	}

	if (lastX != (int)x || lastY != (int)y) {
		bool grow = false;
		if (apple.x == (int)x && apple.y == (int)y) {
			apple.reposition(board);
			++nSegments;
			if(nSegments > 1)
				segments[nSegments - 1] = segments[nSegments - 2];
			grow = true;
		}
		for (int i = nSegments - 1; i > 0; --i) {
			segments[i] = segments[i - 1];
		}
		segments[0] = { lastX, lastY };
	}
}

void Snake::draw(Board& board) const {
	board.drawCell((int)x, (int)y, headColor);
	for (int i = 0; i < nSegments; ++i) {
		board.drawCell(segments[i].x, segments[i].y, bodyColor);
	}
}
