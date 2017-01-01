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
	gfx.DrawRect(offsetX + x0*cellSize + 1, offsetY + y0*cellSize + 1, cellSize - 2, cellSize - 2, c);
}

void Board::drawCircle(int x0, int y0, Color c) {
	assert(x0 >= 0 && y0 >= 0 && x0 < width && y0 < height);
	gfx.DrawCircle(offsetX + x0*cellSize + cellSize/2, offsetY + y0*cellSize + cellSize/2, cellSize/2, c);
}

void Board::drawImage(Image& img, int x0, int y0) {
	img.draw(gfx, offsetX + x0*cellSize, offsetY + y0*cellSize);
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
