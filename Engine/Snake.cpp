#include "Snake.h"



Snake::Snake(int x, int y, direction dir, const unsigned char controls[], Color BaseColor, bool controlledByPad, int padInd) : dir(dir), byPad(controlledByPad), padInd(padInd) {
	if (BaseColor.GetR() >= 200) color = "Czerwony";
	else if (BaseColor.GetG() >= 200) color = "Zielony";
	else if (BaseColor.GetB() >= 200) color = "Niebieski";
	else color = "Turkusowy";

	if (dir == up) {
		++x;
		segments.push_back({ x, y + 1 });
		segments.push_back({ x, y + 2 });
	}
	else if (dir == down) {
		--x;
		segments.push_back({ x, y - 1 });
		segments.push_back({ x, y - 2 });
	}
	else if (dir == left) {
		x -= 5;
		--y;
		segments.push_back({ x + 1, y });
		segments.push_back({ x + 2, y });
	}
	else if (dir == right) {
		x += 5;
		++y;
		segments.push_back({ x - 1, y });
		segments.push_back({ x - 2, y });
	}
	this->x = (float)x;
	this->y = (float)y;

	for (int i = 0; i < 4; i++) {
		this->controls[i] = controls[i];
	}

	bodyColors[0] = BaseColor;
	bodyColors[1] = { (unsigned char)(BaseColor.GetR()*0.7), (unsigned char)(BaseColor.GetG()*0.7) , (unsigned char)(BaseColor.GetB()*0.7) };
}

Snake::~Snake() {
}

void Snake::update(const Board& board, const Keyboard& kbd, const Controller& pad, std::vector<Apple>& apples, float dt, std::vector<Obstacle>& obstacles, const std::vector<Snake>& sneks) {
	if (accelerated) {
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<float> duration = now - accelerationTime;
		if (duration.count() >= 10.0f) {
			accelerated = false;
			speed -= accelerationValue;
		}
	}


	int lastX = (int)x, lastY = (int)y;

	if (dir == left) x -= speed * dt;
	else if (dir == up) y -= speed * dt;
	else if (dir == right) x += speed * dt;
	else y += speed * dt;

	if (x < 0) x = board.getWidth() - speed*dt;
	if (y < 0) y = board.getHeight() - speed*dt;
	if (x >= board.getWidth()) x = 0;
	if (y >= board.getHeight()) y = 0;

	bool moved = lastX != (int)x || lastY != (int)y;

	if ((!byPad && kbd.KeyIsPressed(controls[0]) || byPad && pad.getVY(padInd) == -1) && dir != down) {
		if (segments[0].x == lastX || segments[0].x == (int)x)
			pending = up;
		else {
			dir = up;
			pending = none;
		}
	}
	else if ((kbd.KeyIsPressed(controls[2]) || byPad && pad.getVY(padInd) == 1) && dir != up) {
		if (segments[0].x == lastX || segments[0].x == (int)x)
			pending = down;
		else {
			dir = down;
			pending = none;
		}
	}
	if ((kbd.KeyIsPressed(controls[1]) || byPad && pad.getVX(padInd) == 1) && dir != left) {
		if (segments[0].y == lastY || segments[0].y == (int)y)
			pending = right;
		else {
			dir = right;
			pending = none;
		}
	}
	else if ((kbd.KeyIsPressed(controls[3]) || byPad && pad.getVX(padInd) == -1) && dir != right) {
		if (segments[0].y == lastY || segments[0].y == (int)y)
			pending = left;
		else {
			dir = left;
			pending = none;
		}
	}

	if (moved) {
		if (pending != none) {
			dir = pending;
			pending = none;
		}

		bool eaten = false;
		for (int i = 0; i < apples.size(); ++i) {
			if (apples[i].x == (int)x && apples[i].y == (int)y) {
				if (lastAppleEaten == apples[i].type) {
					appleCombo++;
					if (appleCombo == 3) {
						apples[i].fireEffect(board, sneks, *this, obstacles, apples);
						appleCombo = 0;
						score += 5;
					}
				}
				else {
					appleCombo = 1;
					score++;
					lastAppleEaten = apples[i].type;
				}

				apples[i] = apples[apples.size() - 1];
				apples.pop_back();

				speed += 0.1f;
				eaten = true;
				break;
			}
		}
		if (eaten) {
			if (segments.size() >= 23) {
				while (segments.size() >= 2) {
					obstacles.push_back({ segments.back().x, segments.back().y });
					segments.pop_back();
				}
			}
		}
		else if (segments.size())
			segments.pop_back();
		segments.push_front({ lastX, lastY });
	}
}

bool Snake::deathCheck(const std::vector<Obstacle>& obstacles, const std::vector<Snake>& sneks) const {
	for (int i = 0; i < sneks.size(); ++i) {
		if (this == &sneks[i]) continue;
		Segment head = { (int)x, (int)y };
		for (int j = 0; j < sneks[i].segments.size(); j++) {
			if (head == sneks[i].segments[j]) return true;
		}
	}

	for (int i = 0; i < segments.size(); i++) {
		if (segments[i] == Segment((int)x, (int)y)) return true;
		for (int j = i + 1; j < segments.size(); j++) {
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

void Snake::reset(int x, int y) {
	dir = up;
	this->x = (float)x;
	this->y = (float)y;
}

void Snake::accelerate() {
	speed += accelerationValue;
	accelerationTime = std::chrono::steady_clock::now();
	accelerated = true;
}

bool Snake::isTooClose(const Apple & apple) const {
	if (abs(apple.x - (int)x) <= 2 && abs(apple.y - (int)y) <= 2) return true;
	else {
		for (int i = 0; i < segments.size(); ++i) {
			if (abs(segments[i].x - apple.x) <= 2 && abs(segments[i].y - apple.y) <= 2) return true;
		}
	}
	return false;
}

void Snake::draw(Board& board) const {
	board.drawCell((int)x, (int)y, headColor);
	for (int i = 0; i < segments.size(); ++i)
		board.drawCell(segments[i].x, segments[i].y, bodyColors[i % 2]);
}
