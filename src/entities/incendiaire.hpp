#pragma once

#include "../entities/FSM.hpp""


class Incendiaire : public Ennemy {
public:
	Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	//float life = 5;
	void rangedAttack(float deltaTime) override;
	//radiusDetection = 50;
//private : 
	//float x, y;

	//Animation attackAnim, walkAnim, standAnim, hitAnim;
};