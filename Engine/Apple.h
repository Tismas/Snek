#pragma once

#include "Image.h"
#include "Board.h"
#include "Colors.h"
#include "Obstacle.h"
#include "Projectile.h"

#include <vector>
#include <chrono>

class Snake;

#define COLORS_COUNT 6
enum types {
	violet,
	orange,
	blue,
	green,
	yellow,
	red
};

class Apple {
	int x, y;
	int type;
	static bool initialized;
	void initType();
	void initImages();
public:
	static std::vector<Image> appleImages;
	Apple(int x, int y);
	Apple(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles);
	~Apple();

	void draw(Board& board) const;
	void setPos(int x, int y);
	void reposition(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles);
	void fireEffect(const Board& board, const std::vector<Snake>& sneks, Snake& snek, std::vector<Obstacle>& obstacles, std::vector<Apple>& apples, std::vector<Projectile>& projectiles, bool& raining, std::chrono::steady_clock::time_point& rainStart);

	friend class Snake;
};

