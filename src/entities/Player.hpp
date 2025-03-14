#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "../map/Tiles.hpp"

class Player : public Entity {
public:
	Player();
	~Player();
	void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime) override;
	void jump();
	void deplacement(float deltaTime);
	void border();
	void collide(const std::vector<std::unique_ptr<Tiles>>& tiles);
	float attack();
	void updateHUDEnergy(sf::View& view);

	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::RectangleShape getShapeHUDEnergy() const;
	sf::RectangleShape getShapeFillEnergy() const;
	std::vector<Projectile> getProj() const;
	sf::Sprite getProjShape(Projectile& proj) const;

	void rangedAttack();
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);

	sf::Sprite swordSprite;
	sf::Sprite smokeSprite;
	sf::Sprite playerSprite;
	std::vector<Projectile> projectiles;

private:
	sf::RectangleShape shapeEnergy, shapeFillEnergy;
	sf::Clock attackClock;
	sf::Clock attackDurationClock;
	sf::Clock rangedAttackClock;

	Assets assets;

	float velocityY;
	float velocityX = 0;
	float gravity;
	bool isOnGround;
	int jumpCount;
	float jumpTime = 0.0f;
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