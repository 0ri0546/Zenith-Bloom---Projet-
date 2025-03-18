#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "../map/Tiles.hpp"
#include "../systems/Animation.hpp"

class Player : public Entity {
public:
	Player(sf::Texture& texture);
	~Player();
	void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime) override;
	void jump(float deltaTime);
	void deplacement(float deltaTime);
	void collide(const std::vector<std::unique_ptr<Tiles>>& tiles);
	float attack(float deltaTime);
	void updateHUD(sf::View& view);
	bool takeDamage(sf::Sprite projEnnemi, float deltaTime);

	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::Sprite getSpriteHUDEnergy() const;
	sf::RectangleShape getShapeFillEnergy() const;
	std::vector<Projectile> getProj() const;
	sf::Sprite getProjShape(Projectile& proj) const;
	sf::Sprite getDaySprite() const;
	sf::Sprite getNightSprite() const;

	void rangedAttack();
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);

	
	std::vector<Projectile> projectiles;

private:
	sf::Sprite swordSprite;
	sf::Sprite smokeSprite;
	sf::Sprite playerSprite;
	sf::RectangleShape shapeEnergy, shapeFillEnergy;
	sf::Clock attackClock;
	sf::Clock attackDurationClock;
	sf::Clock rangedAttackClock;
	sf::Clock takeDamageClock;


	Assets assets;

	sf::Sprite daySprite, nightSprite, hudEnergySprite;

	float velocityY;
	float velocityX;
	float gravity;
	bool isOnGround;
	int jumpCount;
	float jumpTime;
	const int maxJumps = 2;
	bool canJump;
	bool lastDepIsLeft;
	int vie;
	bool hangedToWallsLeft;
	bool hangedToWallsRight;
	float depX;
	float bounce;

	float energy;
	float maxJetpackEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float damage;

	int hp;

	Animation 
		jumpAnimation,
		walkToLeftAnimation,
		walkToRightAnimation,
		staticAnimation,
		hangedToLefAnimation,
		hangedToRightAnimation,

		takeDamageAnimation,
		deathAnimation,
		healAnimation,
		attackAnimation,
		rangedAttackAnimation,
		repairAnimation,
		smokeAnimation;

	bool isAttacking;
	bool setAnimationDamage;

};

#endif