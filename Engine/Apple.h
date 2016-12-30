#pragma once

#include "Board.h"
#include "Colors.h"
#include "Obstacle.h"
#include <vector>

class Snake;

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
	static std::vector<Color> colors;
	void initType();
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

