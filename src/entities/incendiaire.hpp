#pragma once

#include "../entities/FSM.hpp""


class Incendiaire : public Ennemy {
public:
	Incendiaire(unsigned long long x, unsigned long long y) : Ennemy(x, y) { spriteEnnemy.setTexture(Shared::incendTexture); };
	//float life = 5;


//private : 
	//float x, y;

};