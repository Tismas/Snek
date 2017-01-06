#include "Projectile.h"
#include "Apple.h"
#include "Snake.h"

Image Projectile::img = Image();
Projectile::Projectile(int x, int y, direction dir) : x((float)x), y((float)y), dir(dir) {
	if(!img.loaded)
		img.loadBmp32("./Assets/projectile.bmp");
}


Projectile::~Projectile() {
}

void Projectile::draw(Graphics & gfx) const {
	img.draw(gfx, (int)x, (int)y);
}

bool Projectile::update(std::vector<Obstacle>& obstacles, std::vector<Apple>& apples, const Board& board) {
	if (dir == up) y -= speed;
	else if (dir == down) y += speed;
	else if (dir == left) x -= speed;
	else x += speed;

	for (int i = 0; i < obstacles.size(); ++i) {
		if (obstacles[i].x == floor((x-board.getOffsetX())/20) && obstacles[i].y == floor((y-board.getOffsetY())/20)) {
			apples.push_back(Apple(obstacles[i].x, obstacles[i].y));
			obstacles[i] = obstacles[obstacles.size() - 1];
			obstacles.pop_back();
			return true;
		}
	}
	return false;
}

bool Projectile::shouldBeDeleted(Board& board) const {
	float top = (float)board.getOffsetY(),
		  right = Graphics::ScreenWidth - (float)board.getOffsetX(),
		  bottom = Graphics::ScreenHeight - (float)board.getOffsetY(),
		  left = (float)board.getOffsetX();

	return x <= left || (x+img.width) >= right || y <= top || (y+img.height) >= bottom;
}
