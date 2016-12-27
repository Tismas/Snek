#pragma once

#include <assert.h>

#include "Colors.h"
#include "Graphics.h"

class Board {
	const int width, height, cellSize, offsetX, offsetY;
	static constexpr Color borderColor = Colors::Gray;
	Graphics& gfx;
public:
	Board(Graphics& gfx, int width = 45, int height = 35, int cellSize = 15);
	~Board();

	void drawCell(int x, int y, Color c);
	void drawBorder();

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
};

