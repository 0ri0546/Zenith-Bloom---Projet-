#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	// constructeur
	Drone(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	
	// void
	void attack(Player& player, float deltaTime);
	void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) override;
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);
	
	std::vector<Projectile>& getProj();
	sf::Vector2f initialPosition;

	Assets assets;
	Direction currentDirection = LEFT;
	sf::Clock attackClock, attackClockDuration;

	float directionTimer = 0.0f;
	bool isAttacking;

	std::vector<Projectile> projectilesDrone;
	sf::Sprite getProjShape(Projectile& proj) const;

	Animation deplacementAnimation;
};