#pragma once

#include "Board.h"
#include "Colors.h"
#include <vector>

class Apple {
	int x, y;
	int type;
	static std::vector<Color> colors;
public:
	Apple(int x, int y);
	~Apple();

	void draw(Board& board) const;
	void setPos(int x, int y);
	void reposition(const Board& board);

	friend class Snake;
};

