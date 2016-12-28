#include "Snake.h"



Snake::Snake(int x, int y) : x((float)x), y((float)y) {
	speed = 3.5f;
	segments.push_back({ x, y + 1 });
	segments.push_back({ x, y + 2 });
}

Snake::~Snake() {
}

void Snake::update(const Board& board, const Keyboard& kbd, Apple& apple, float dt, std::vector<Obstacle>& obstacles) {
	int lastX = (int)x, lastY = (int)y;

	if (dir == left) x-=speed * dt;
	else if (dir == up) y -= speed * dt;
	else if (dir == right) x += speed * dt;
	else y += speed * dt;

	if (x < 0) x = board.getWidth() - speed*dt;
	if (y < 0) y = board.getHeight() - speed*dt;
	if (x >= board.getWidth()) x = 0;
	if (y >= board.getHeight()) y = 0;

	if (kbd.KeyIsPressed(VK_UP) && dir != down) {
		dir = up;
	}
	else if (kbd.KeyIsPressed(VK_DOWN) && dir != up) {
		dir = down;
	}
	else if (kbd.KeyIsPressed(VK_LEFT) && dir != right) {
		dir = left;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) && dir != left) {
		dir = right;
	}

	if (lastX != (int)x || lastY != (int)y) {
		if (apple.x == (int)x && apple.y == (int)y) {
			apple.reposition(board, obstacles);
			speed += 0.1f;
			if (segments.size() >= 10) {
				while (segments.size() >= 2) {
					obstacles.push_back({ segments.back().x, segments.back().y });
					segments.pop_back();
				}
			}
		}
		else if(segments.size())
			segments.pop_back();
		segments.push_front({ lastX, lastY });
	}
}

bool Snake::deathCheck(const std::vector<Obstacle>& obstacles) const {
	for (int i = 0; i < segments.size(); i++) {
		if (segments[i] == Segment((int)x, (int)y)) return true;
		for (int j = i+1; j < segments.size(); j++) {
			if (segments[i] == segments[j])
				return true;
		}
	}
	
	for (int j = 0; j < obstacles.size(); j++) {
		if (Segment((int)x, (int)y) == obstacles[j]) return true;
		for (int i = 0; i < segments.size(); i++) {
			if (segments[i] == obstacles[j])
				return true;
		}
	}

	return false;
}

void Snake::draw(Board& board) const {
	board.drawCell((int)x, (int)y, headColor);
	for (int i = 0; i < segments.size(); ++i)
		board.drawCell(segments[i].x, segments[i].y, bodyColors[i % 2]);
}
