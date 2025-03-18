#pragma once

#include "../entities/FSM.hpp""


class Incendiaire : public Ennemy {
public:
	Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, float xT, float yT);
	//float life = 5;

	//radiusDetection = 50;
//private : 
	//float x, y;

	//Animation attackAnim, walkAnim, standAnim, hitAnim;
};