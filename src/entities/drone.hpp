#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	Drone(unsigned long long x, unsigned long long y) : Ennemy(x, y) { spriteEnnemy.setTexture(Shared::droneTexture); };
	//float life = 5;


//private : 
	//float x, y;

};