#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "../entities/Player.hpp"
#include "Projectile.hpp"


enum ennemyState {
	PATROL,
	SEARCH,
	CHASE,
	DEAD
};

class Ennemy {
public : 
	Ennemy(unsigned long long x, unsigned long long y);

	void patrol(Player& player);
	void chase(Player& player);


	void collision(Player& player, vector<Projectile>& projectile, vector<Ennemy>& ennemies);
	void colEnnemyToEnnemy(vector<Ennemy>& ennemies);
	void colEnnemyToPlayer(Player& player, vector<Ennemy>& ennemies);
	void colEnnemiToGround(vector<Ennemy>& ennemies, vector<Platform>& platforms);
	

	void draw(sf::RenderWindow& window);
	void runEnnemy(Player& player, sf::RenderWindow& window, vector<Projectile>& projectile, vector<Ennemy>& ennemies, vector<Platform>& platforms, float deltaTime);
	
	
	void rangedAttack();
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);

	sf::Sprite getSprite() const;
	std::vector<Projectile> getProj() const;
	sf::Sprite getProjShape(Projectile& proj) const;

private : 



	ennemyState currentState;
	Assets assets;
	sf::Clock rangedAttackClock;

	std::vector<Projectile> projectiles;
	vector<sf::Sprite> spritEnnemies;
	vector<sf::CircleShape> detectionCircles;
	sf::Vector2f moveForCol;

	size_t pathIndex;
	int life = 3;

	float radiusDetection = 200.f;
	float speed;
	float gravity; 
	float velocityY;

	bool stop = false;
	bool isWakable = true;
	bool onTheGround = false; 
	/*float searchTime;
	float attackCooldown;*/

	float x, y;
	float scaleEnnemy = 1; 
	bool lastDepIsLeft;

	sf::Sprite spriteEnnemy;
	//sf::CircleShape detectionCircle;
};

#endif
