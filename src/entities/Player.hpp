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
	void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime, bool isDay, bool isInTheSun) override;
	void jump(float deltaTime);
	void deplacement(float deltaTime);
	void collide(const std::vector<std::unique_ptr<Tiles>>& tiles);
	float attack(float deltaTime);
	void updateHUD(sf::View& view);
	bool takeDamage(sf::Sprite projEnnemi, float deltaTime);
	void animate(float deltaTime);
	void statsManager(bool isDay, bool isInTheSun);

	sf::Sprite getShape() const;
	sf::Sprite getShapeAtk() const;
	sf::Sprite getShapeSmoke() const;
	sf::Sprite getLifeBarSprite() const;
	sf::Sprite getLifeBar2Sprite() const;
	sf::Sprite getEnergyBarSprite() const;
	sf::Sprite getProgressBarSprite() const;
	sf::Sprite getSurchauffeBarSprite() const;
	sf::RectangleShape getShapeFillEnergy() const;
	sf::RectangleShape getShapeFillHP() const;
	sf::RectangleShape getShapeSurchauffe() const;
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
	bool getCanDisplayGameOverBool() const;

	void rangedAttack();
	void updateProjectiles(float deltaTime, sf::RenderWindow& window);

	std::vector<Projectile> projectiles;
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
	sf::Clock takeDamageClock;
	sf::Clock death;

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
	bool isDead;
	bool hangedToWallsLeft;
	bool hangedToWallsRight;
	float depX;
	float bounce;

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
	bool isAttacking;
	bool isRangedAttacking;
	bool takingDamage;
	float progress;
	bool canDisplayGameOverBool;
	bool isRepairing;

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
		smokeAnimation;
};

#endif