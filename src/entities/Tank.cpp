#pragma once

#include "../entities/Tank.hpp"


Tank::Tank(unsigned long long x, unsigned long long y) : Ennemy(x, y) {
	spriteEnnemy.setTexture(Shared::tankTexture);

	life = 7;
	speed = 0.3;
	currentState = PATROL;
	radiusDetection = 300;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);

}