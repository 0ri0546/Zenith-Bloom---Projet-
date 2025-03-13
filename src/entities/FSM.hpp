#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "../entities/Player.hpp"
#include "../entities/Projectile.hpp"
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
	void chase(Player& player, vector<Ennemy>& ennemies);

	void collision(Player& player, vector<Projectile>& projectile, vector<Ennemy>& ennemies);
	void colEnnemyToEnnemy(vector<Ennemy>& ennemies);

	/*void seachPlayer();
	void die();*/

	void shoot(Player& player, vector<Ennemy>& ennemies);
	void updateShoot(float deltaTime, sf::RenderWindow& window, vector<Ennemy>& ennemies);
	std::vector<Projectile> getProj() const;

	sf::Sprite getProjShape(Projectile& proj) const;
	

	void runEnnemy(Player& player, sf::RenderWindow& window, vector<Projectile>& projectile, vector<Ennemy>& ennemies, float deltaTime);
	Assets assets;

	ennemyState currentState;
	std::vector<Projectile> projectiles;

private : 

	
	size_t pathIndex = 0;

	int life = 3;

	float radiusDetection = 200.f;
	float speed;
	float x, y;
	float scaleEnnemy = 1;

	bool stop = false;
	bool isWakable = true;

	vector<sf::Sprite> spritEnnemies;
	vector<sf::CircleShape> detectionCircles;
	//std::vector<Projectile> projectiles;

	sf::Vector2f moveForCol; 

	sf::Sprite spriteEnnemy;

	sf::Clock rangedAttackClock;
	
	//sf::CircleShape detectionCircle;
	
	 

	

};













#endif
