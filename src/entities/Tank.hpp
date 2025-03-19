#pragma once

#include "../entities/FSM.hpp"


class Tank : public Ennemy {
public :
	Tank(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	//float life = 5;


//private : 
	//float x, y;

};