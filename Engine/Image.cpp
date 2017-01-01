#include "Image.h"

#include <iostream>

Image::Image() {
	pixels = NULL;
	width = 0;
	height = 0;
}

Image::~Image() {
	delete[] pixels;
	pixels = NULL;
}

void Image::loadBmp32(const std::string& filename) {
	std::ifstream img(filename, std::ios::binary);
	int offset;
	img.seekg(10, std::ios::beg);
	img.read((char*)&offset, 4);

	img.seekg(18, std::ios::beg);
	img.read((char*)&width, 4);
	img.read((char*)&height, 4);

	pixels = new Color[height*width];
	memset(pixels, 0, width*height * sizeof(int8_t));

	img.seekg(offset, std::ios::beg);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Color& pixel = pixels[(width - 1 - i)*width + j];
			unsigned char r, g, b, a;
			img.read((char*)&b, 1);
			img.read((char*)&g, 1);
			img.read((char*)&r, 1);
			img.read((char*)&a, 1);
			pixel.SetR(r);
			pixel.SetG(g);
			pixel.SetB(b);
			pixel.SetA(a);
		}
	}
}

// TODO: Dodac obsluge rysowania na inna wysokosc/szerokosc
void Image::draw(Graphics & gfx, int x, int y, int destWidth, int destHeight) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Color& pixel = pixels[i*width + j];
			if (pixel.GetA() != 0)
				gfx.PutPixel(x+j, y+i, pixel);
		}
	}
}
