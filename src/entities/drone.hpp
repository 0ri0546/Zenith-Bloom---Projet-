#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	enum Direction {
		LEFT,  // Gauche
		RIGHT, // Droite
		UP,    // Haut
		DOWN   // Bas
	};
	Drone(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	void attack(Player& player, float deltaTime);
	void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) override;
	std::vector<Projectile>& getProj();
	bool isAttacking;
	sf::Vector2f initialPosition;
	sf::Clock attackClock, attackClockDuration;

	Assets assets;
	Direction currentDirection = LEFT;  // Direction actuelle du drone
	float directionTimer = 0.0f;

	std::vector<Projectile> projectilesDrone;
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);
	sf::Sprite getProjShape(Projectile& proj) const;

	Animation deplacementAnimation;
};