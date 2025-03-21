#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "../map/Tiles.hpp"
#include "../map/Reparable.hpp"
#include "../systems/Animation.hpp"
#include "../systems/audioManager.hpp"

class Player : public Entity {
public:
	// constructeur et destructeur
	Player(sf::Texture& texture);
	~Player();

	// void
	void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime, bool isDay, bool isInTheSun) override;
	void jump(float deltaTime);
	void deplacement(float deltaTime);
	void collide(const std::vector<std::unique_ptr<Tiles>>& tiles);
	void rangedAttack();
	void updateHUD(sf::View& view);
	void animate(float deltaTime);
	void statsManager(bool isDay, bool isInTheSun);
	void throwWater();
	void setTakingDamageBool(bool takingDamage);
	void augmenterEnergie(int quantite);
	void augmenterHP(int quantite);
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);
	void resetPlayer();
	void fix(const std::vector<std::unique_ptr<Reparable>>& re);


	// getters float
	float attack(float deltaTime);
	float getEnergie() const;
	float getHP() const;

	// getters bools
	bool takeDamage(sf::Sprite projEnnemi, float deltaTime);
	bool takeDamageSimple(float deltaTime);
	bool getTakingDamageBool() const;
	bool getCanDisplayGameOverBool() const;

	// getters sprites
	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::Sprite getLifeBarSprite() const;
	sf::Sprite getLifeBar2Sprite() const;
	sf::Sprite getEnergyBarSprite() const;
	sf::Sprite getProgressBarSprite() const;
	sf::Sprite getSurchauffeBarSprite() const;
	sf::Sprite getProjShape(Projectile& proj) const;
	sf::Sprite getProjWaterShape(Projectile& proj) const;
	sf::Sprite getDaySprite() const;
	sf::Sprite getNightSprite() const;

	// getters shapes
	sf::RectangleShape getShapeFillEnergy() const;
	sf::RectangleShape getShapeFillHP() const;
	sf::RectangleShape getShapeSurchauffe() const;

	// getter vecteurs
	std::vector<Projectile> getProj() const;
	std::vector<Projectile> getProjWater() const;

	// veteurs
	std::vector<Projectile> projectiles;
	std::vector<Projectile> projectilesWater;

	// variables
	bool setAnimationDamage;
	bool canAttack;

private:
	sf::Sprite swordSprite, smokeSprite, playerSprite;
	sf::Sprite daySprite, nightSprite, lifeBarSprite, energyBarSprite, progressBarSprite, surchauffeBarSprite;

	sf::RectangleShape shapeFillEnergy, shapeFillHP, shapeFillSurchauffe;

	sf::Clock attackClock;	
	sf::Clock attackDurationClock;
	sf::Clock rangedAttackClock;
	sf::Clock rangedAttackClockDuration;
	sf::Clock throwWaterClock;
	sf::Clock throwWaterClockDuration;
	sf::Clock takeDamageClock;
	sf::Clock death;

	Assets assets;

	float velocityY;
	float velocityX;
	float gravity;
	float depX;
	float bounce;
	float jumpTime;

	float energy;
	float surchauffe;
	float maxSurchauffe;
	float surchauffeRecharge;
	float maxEnergy;
	float jetpackPower;
	float energyConsumption;
	float energyRecharge;
	float hpRecharge;
	float damage;
	float hp;
	float maxHp;
	float progress;

	bool isOnGround;
	bool canJump;
	bool lastDepIsLeft;
	bool isDead;
	bool hangedToWallsLeft;
	bool hangedToWallsRight;
	bool isAttacking;
	bool isRangedAttacking;
	bool takingDamage;
	bool canDisplayGameOverBool;
	bool isRepairing;
	bool isThrowingWater;

	int jumpCount;
	const int maxJumps = 2;

	Animation
		jumpToLeftAnimation, jumpToRightAnimation,
		walkToLeftAnimation, walkToRightAnimation,
		staticToLeftAnimation, staticToRightAnimation,
		hangedToLefAnimation, hangedToRightAnimation,
		takeDamageToLeftAnimation, takeDamageToRightAnimation,
		deathToLeftAnimation, deathToRightAnimation,
		healAnimation,
		attackToLeftAnimation, attackToRightAnimation,
		rangedAttackToLeftAnimation,
		rangedAttackToRightAnimation,
		repairToLeftAnimation,
		repairToRightAnimation,
		smokeAnimation,
		throwWaterToLeftAnimation, throwWaterToRightAnimation;
};

#endif