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

	void loadBmp32(const std::string& filename);

	void draw(Graphics& gfx, int x,int y, int width, int height);
};

