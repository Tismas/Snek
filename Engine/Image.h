#pragma once

#include <string>
#include <fstream>

#include "Graphics.h"

class Image {
	Color* pixels;
	int width, height;
public:
	Image();
	~Image();

	void resample(int newWidth, int newHeight);
	void loadBmp32(const std::string& filename);

	void draw(Graphics& gfx, int x,int y);
};

