#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../systems/Datas.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "Entity.hpp"

class Player : public Entity {
public:
	Player();
	void update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view) override;
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

	sf::Sprite swordSprite;
	sf::Sprite smokeSprite;
	sf::Sprite playerSprite;

private:
	sf::RectangleShape shapeEnergy, shapeFillEnergy;
	sf::Clock attackClock;
	sf::Clock attackDurationClock;

	float velocityY;
	float velocityX = 0;
	float gravity;
	bool isOnGround;
	int jumpCount;
	const int maxJumps = 2;
	bool canJump;
	bool lastDepIsLeft;
	int vie = 3;

	float energy;
	float maxJetpackEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float damage;

	int hp;
};

#endif