#pragma once

#include "Snake.h"
#include "Image.h"

class UICombo {
	const Snake& snek;
	Image* img;
	static Image empty;
	int appleType;
	const int snekInd;
public:
	UICombo(const Snake& snek, int ind);
	~UICombo();

	void draw(Graphics& gfx);
};

