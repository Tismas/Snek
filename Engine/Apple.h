#pragma once

#include "Board.h"
#include "Colors.h"

class Apple {
	int x, y;
	Color appleColor = Colors::Red;
public:
	Apple(int x, int y);
	~Apple();

	void draw(Board& board) const;
	void setPos(int x, int y);
	void reposition(const Board& board);

	friend class Snake;
};

