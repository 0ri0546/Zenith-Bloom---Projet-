#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "../entities/Player.hpp"
#include "Projectile.hpp"
#include "../map/Platform.hpp"

enum ennemyState {
    PATROL,
    SEARCH,
    CHASE,
    DEAD
};

class Ennemy {
public:
    Ennemy(unsigned long long x, unsigned long long y);
    ~Ennemy();

    void patrol(Player& player);
    void chase(Player& player);

    void collision(Player& player, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies);
    void colEnnemyToEnnemy(vector<std::unique_ptr<Ennemy>>& ennemies);
    void colEnnemyToPlayer(Player& player, vector<std::unique_ptr<Ennemy>>& ennemies);
    void colEnnemiToGround(vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles);

    void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime);

    void rangedAttack();
    void updateProjectiles(float deltaTime, sf::RenderWindow& window);
	void fillEmptySpacesWithShadows(std::vector<std::unique_ptr<Tiles>>& tiles);

    sf::Sprite getSprite() const;
    std::vector<Projectile>& getProj();
    sf::Sprite getProjShape(Projectile& proj) const;
    
    float x, y;
    int life = 3;


//private:
    ennemyState currentState;
    Assets assets;
    sf::Clock rangedAttackClock;

    std::vector<Projectile> projectiles;
    std::vector<sf::Sprite> spritEnnemies;
    std::vector<sf::CircleShape> detectionCircles;
    sf::Vector2f moveForCol;

    size_t pathIndex;
    

    float radiusDetection = 200.f;
    float speed;
    float gravity;
    float velocityY;
    float maxFallSpeed = 800;
    float boxCol1;
    float boxCol2;

    bool stop = false;
    bool isWakable = true;
    bool onTheGround = false;

    
    float scaleEnnemy = 1;
    bool lastDepIsLeft;

    sf::Sprite spriteEnnemy;
};

#endif
