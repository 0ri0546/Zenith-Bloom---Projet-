#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"





class Ennemy {

public : 
	Ennemy(float x, float y); 

	sf::Sprite getSprite() const;

	void move();
	void attack();
	void seachPlayer();
	void die();
	void draw(sf::RenderWindow& window);
	Assets assets;

private : 

	int life = 3;
	float radiusDetection = 50.f;
	float searchTime;
	float attackCooldown;

	sf::Sprite spriteEnnemy;
	sf::CircleShape detectionCircle;
	
	float scaleEnnemy = 1; 

	

};













#endif
