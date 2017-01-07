#include "Droplet.h"
#include "Graphics.h"

Droplet::Droplet(int x, int y, int z) : x((float)x), y((float)y), z((float)z) {
	speed = z / 0.01f;
	length = 1.0f / z * 20;
}


Droplet::~Droplet() {
}

void Droplet::draw(Color* backbuffer, Graphics& gfx, int screenWidth) const {
	for (int i = 0; i < length; i++) {
		if (y - i > 0)
			backbuffer[((int)y-i)*screenWidth + (int)x].SetB(255 - i*5);
	}
}

void Droplet::update(int screenHeight, float dt) {
	y += speed*dt;
	if (y >= screenHeight-10)
		y = 0;
}