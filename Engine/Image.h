#pragma once

#include <string>
#include <fstream>

#include "Graphics.h"

class Image {
	Color* pixels;
public:
	int width, height;
	bool loaded = false;

	Image();
	~Image();

	void resample(int newWidth, int newHeight);
	void loadBmp32(const std::string& filename);

	void draw(Graphics& gfx, int x,int y);
	void draw(Graphics & gfx, int x, int y, int x0, int y0, int w, int h);
};

