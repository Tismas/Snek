#pragma once

#include <string>
#include <fstream>

#include "Graphics.h"

class Image {
	unsigned char* pixels;
	int width, height;
public:
	Image(const std::string& filename);
	~Image();

	void draw(Graphics& gfx);
};

