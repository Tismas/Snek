#pragma once

#include <vector>
#include "Image.h"
#include "Graphics.h"
#include "Obstacle.h"

class Apple;

enum direction;

class Projectile {
	float x, y, speed = 2.5f;
	static Image img;
	direction dir;
public:
	Projectile(int x, int y, direction dir);
	~Projectile();

	void draw(Graphics& gfx) const;
	bool update(std::vector<Obstacle>& obstacles, std::vector<Apple>& apples, const Board& board);
	bool shouldBeDeleted(Board& board) const;
};

