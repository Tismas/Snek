#pragma once

#include "Colors.h"

class Graphics;

class Droplet {
	float x, y, z;
	float speed;
	int length;
public:
	Droplet(int x, int y, int r);
	~Droplet();
	void draw(Color* backbuffer, Graphics& gfx, int screenWidth) const;
	void update(int screenHeight, float dt);
};

