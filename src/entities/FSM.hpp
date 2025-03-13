#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "../entities/Player.hpp"
//#include "../systems/pathfinfing.hpp"
//#include "../systems/grid.hpp"

enum ennemyState {
	PATROL,
	SEARCH,
	CHASE,
	DEAD
};

class Ennemy {

public : 
	Ennemy(unsigned long long x, unsigned long long y);

	sf::Sprite getSprite() const;

	void patrol(Player& player);
	void chase(Player& player);

	void collision(Player& player, vector<Projectile>& projectile, vector<Ennemy>& ennemies);
	void colEnnemyToEnnemy(vector<Ennemy>& ennemies);

	/*void seachPlayer();
	void die();*/
	void draw(sf::RenderWindow& window);

	void runEnnemy(Player& player, sf::RenderWindow& window, vector<Projectile>& projectile, vector<Ennemy>& ennemies);
	Assets assets;

	ennemyState currentState;

private : 

	
	size_t pathIndex = 0;
	int life = 3;
	float radiusDetection = 200.f;
	 float speed;

	bool stop = false;
	bool isWakable = true;
	vector<sf::Sprite> spritEnnemies;
	vector<sf::CircleShape> detectionCircles;
	sf::Vector2f moveForCol; 
	/*float searchTime;
	float attackCooldown;*/

	sf::Sprite spriteEnnemy;
	
	//sf::CircleShape detectionCircle;
	
	float x, y;
	float scaleEnnemy = 1; 

	

};













#endif
