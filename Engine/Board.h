#pragma once

#include <assert.h>

#include "Colors.h"
#include "Graphics.h"

class Board {
	const int width, height, cellSize, offsetX, offsetY;
	static constexpr Color borderColor = Colors::Gray;
	Graphics& gfx;
public:
	Board(Graphics& gfx, int width = 39, int height = 29, int cellSize = 20);
	~Board();

	void drawCell(int x, int y, Color c);
	void drawCircle(int x, int y, Color c);
	void drawBorder();

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
};

