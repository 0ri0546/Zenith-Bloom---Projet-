#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once

#include "Datas.hpp"
#include "Platform.hpp"
#include "AssetLoader.hpp"

class Player {
public:
	Player();
	void update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view);
	void jump();
	void deplacement();
	void border();
	void collide(const std::vector<Platform>& platforms);
	float attack();
	void updateHUDEnergy(sf::View& view);

	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::RectangleShape getShapeHUDEnergy() const;
	sf::RectangleShape getShapeFillEnergy() const;

private:
	sf::RectangleShape shapeAtk, shapeRangedAtk, shapeSmoke, shapeEnergy, shapeFillEnergy;
	sf::Clock attackClock;
	sf::Clock attackDurationClock;

	float velocityY;
	float gravity;
	bool isOnGround;
	int jumpCount;
	const int maxJumps = 2;
	bool canJump;
	bool lastDepIsLeft;

	float energy;
	float maxJetpackEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float damage;

	int hp;

};

#endif
