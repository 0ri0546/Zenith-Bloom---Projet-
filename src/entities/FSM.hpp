#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "../entities/Player.hpp"


enum ennemyState {
	PATROL,
	SEARCH,
	CHASE,
	DEAD
};

class Ennemy {

public : 
	Ennemy(); 

	sf::Sprite getSprite() const;

	void patrol(Player& player);
	void chase(Player& player);
	/*void seachPlayer();
	void die();
	void draw(sf::RenderWindow& window);*/

	void runEnnemy(Player& player, sf::RenderWindow& window);
	Assets assets;

	ennemyState currentState;

private : 

	


	int life = 3;
	float radiusDetection = 100.f;
	float searchTime;
	float attackCooldown;

	sf::Sprite spriteEnnemy;
	sf::CircleShape detectionCircle;
	
	
	float scaleEnnemy = 1; 

	

};













#endif
