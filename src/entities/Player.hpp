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
	void animate(float deltaTime);

	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::Sprite getSpriteHUDEnergy() const;
	sf::RectangleShape getShapeFillEnergy() const;
	std::vector<Projectile> getProj() const;
	sf::Sprite getProjShape(Projectile& proj) const;
	sf::Sprite getDaySprite() const;
	sf::Sprite getNightSprite() const;
	bool getTakingDamageBool() const;
	void setTakingDamageBool(bool takingDamage);
	void augmenterEnergie(int quantite);
	float getEnergie() const;
	void augmenterHP(int quantite);
	float getHP() const;

	void rangedAttack();
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);

	std::vector<Projectile> projectiles;
	bool setAnimationDamage;
	bool canAttack;

private:
	sf::Sprite swordSprite, smokeSprite, playerSprite;
	sf::Sprite daySprite, nightSprite, hudEnergySprite;

	sf::RectangleShape shapeEnergy, shapeFillEnergy;

	sf::Clock attackClock;	
	sf::Clock attackDurationClock;
	sf::Clock rangedAttackClock;
	sf::Clock rangedAttackClockDuration;
	sf::Clock takeDamageClock;

	Assets assets;

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
	float energyMax;
	float maxJetpackEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float damage;
	int hp;
	bool isAttacking;
	bool takingDamage;

	Animation 
		jumpToLeftAnimation, jumpToRightAnimation,
		walkToLeftAnimation, walkToRightAnimation,
		staticToLeftAnimation, staticToRightAnimation,
		hangedToLefAnimation, hangedToRightAnimation,
		takeDamageToLeftAnimation, takeDamageToRightAnimation,
		deathToLeftAnimation, deathToRightAnimation,
		healAnimation,
		attackToLeftAnimation, attackToRightAnimation,
		rangedAttackAnimation,
		repairAnimation,
		smokeAnimation;
};

#endif