#include "Image.h"



Image::Image(const std::string& filename) {
	std::ifstream img(filename, std::ios::binary);
	char width[4], height[4];
	img.ignore(18);
	img.read(width, 4);
	img.read(height, 4);
}


Image::~Image() {
}

void Image::draw(Graphics & gfx) {
}
