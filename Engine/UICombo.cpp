#include "UICombo.h"

Image UICombo::empty = Image();

UICombo::UICombo(const Snake & snek, int ind) : snek(snek), snekInd(ind), img(NULL) {
	appleType = snek.getLastAppleEaten();
	empty.loadBmp32("./Assets/appleShape.bmp");
}

UICombo::~UICombo() {
}

void UICombo::draw(Graphics& gfx) {
	int combo = snek.getComboCounter();
	if (appleType != snek.getLastAppleEaten()) {
		appleType = snek.getLastAppleEaten();
		if (appleType == -1) img = NULL;
		else img = &Apple::appleImages[appleType];
	}
	if (img) {
		for (int i = 0; i < combo; ++i) {
			img->draw(gfx, 10 + (i * 20), (snekInd + 1) * 20);
		}
	}
	for (int i = combo; i < 3; ++i) {
		empty.draw(gfx, 10 + (i * 20), (snekInd + 1) * 20);
	}
}
