#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	Drone(unsigned long long x, unsigned long long y, sf::Texture text, float xT, float yT) : Ennemy(x, y, text, xT, yT) { spriteEnnemy.setTexture(Shared::droneTexture); };
	//float life = 5;


//private : 
	//float x, y;

};