#include "Apple.h"
#include "Snake.h"

#include <random>

bool Apple::initialized = false;
std::vector<Image> Apple::appleImages;

void Apple::initType() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> typeDist(0, (int)appleImages.size() - 1);
	type = typeDist(rng);
}

void Apple::initImages() {
	for (int i = 0; i < COLORS_COUNT; ++i)
		appleImages.push_back(Image());

	appleImages[violet].loadBmp32("./Assets/violet.bmp");
	appleImages[orange].loadBmp32("./Assets/orange.bmp");
	appleImages[blue].loadBmp32("./Assets/blue.bmp");
	appleImages[green].loadBmp32("./Assets/green.bmp");
	appleImages[yellow].loadBmp32("./Assets/yellow.bmp");
	appleImages[red].loadBmp32("./Assets/red.bmp");
}

Apple::Apple(int x, int y) : x(x), y(y) {
	if (!initialized) {
		initImages();
		initialized = true;
	}
	initType();
}

Apple::Apple(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles) {
	if (!initialized) {
		initImages();
		initialized = true;
	}
	reposition(board, sneks, obstacles);
}


Apple::~Apple() {
}

void Apple::draw(Board & board) const {
	board.drawImage(appleImages[type], x, y);
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
