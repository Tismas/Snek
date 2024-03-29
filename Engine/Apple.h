#pragma once

#include "Image.h"
#include "Board.h"
#include "Colors.h"
#include "Obstacle.h"
#include <vector>

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
	static std::vector<Image> appleImages;
	void initType();
	void initImages();
public:
	Apple(int x, int y);
	Apple(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles);
	~Apple();

	void draw(Board& board) const;
	void setPos(int x, int y);
	void reposition(const Board& board, const std::vector<Snake>& sneks, const std::vector<Obstacle>& obstacles);
	void fireEffect(const Board& board, const std::vector<Snake>& sneks, Snake& snek, std::vector<Obstacle>& obstacles, std::vector<Apple>& apples);

	friend class Snake;
};

