#pragma once

#include "../entities/FSM.hpp"


class Drone : public Ennemy {
public:
	Drone(unsigned long long x, unsigned long long y, sf::Texture text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	void attack(Player& player, float deltaTime);
	void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) override;

	bool isAttacking;
	sf::Vector2f initialPosition;
	sf::Clock attackClock, attackClockDuration;

	std::vector<Projectile> projectilesDrone;
};