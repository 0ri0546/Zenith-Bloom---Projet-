#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	Drone(unsigned long long x, unsigned long long y, sf::Texture text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY) : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY) { spriteEnnemy.setTexture(Shared::droneTexture); };
	//float life = 5;


//private : 
	//float x, y;

};