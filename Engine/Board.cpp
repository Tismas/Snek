#include "Board.h"



Board::Board(Graphics& gfx, int width, int height, int cellSize): 
	gfx(gfx), 
	width(width), 
	height(height), 
	cellSize(cellSize), 
	offsetX((Graphics::ScreenWidth - cellSize*width) / 2), 
	offsetY((Graphics::ScreenHeight - cellSize*height) / 2)
{
}


Board::~Board() {
}

void Board::drawCell(int x0, int y0, Color c) {
	assert(x0 >= 0 && y0 >= 0 && x0 < width && y0 < height);
	for (int y = y0*cellSize+1; y < y0*cellSize + cellSize-1; ++y) {
		for (int x = x0*cellSize+1; x < x0*cellSize + cellSize-1; ++x) {
			gfx.DrawRect(offsetX + x, offsetY + y, cellSize, cellSize, c);
		}
	}
}

void Board::drawBorder() {
	for (int y = 0; y < height*cellSize; ++y) {
		gfx.PutPixel(offsetX - 1, offsetY + y, borderColor);
		gfx.PutPixel(offsetX + width*cellSize + 1, offsetY + y, borderColor);
	}
	for (int x = 0; x < width*cellSize; ++x) {
		gfx.PutPixel(offsetX + x, offsetY - 1, borderColor);
		gfx.PutPixel(offsetX + x, offsetY + height*cellSize + 1, borderColor);
	}
}
