#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Entity.hpp"
#include "Projectile.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/Animation.hpp"
#include "../systems/audioManager.hpp"


enum ennemyState {
    PATROL,
    SEARCH,
    CHASE,
    NIGHT,
    DEAD
};

class Ennemy {
public:
    Ennemy(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
    ~Ennemy();

    void patrol(Player& player);
    void chase(Player& player);

    void collision(Player& player, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, float deltaTime);
    void colEnnemyToEnnemy(vector<std::unique_ptr<Ennemy>>& ennemies);
    void colEnnemyToPlayer(Player& player, vector<std::unique_ptr<Ennemy>>& ennemies);
    void colEnnemiToGround(vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles);

    virtual void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime);

    virtual void rangedAttack(float deltaTime);

    void updateProjectiles(float deltaTime, sf::RenderWindow& window);
	void fillEmptySpacesWithShadows(std::vector<std::unique_ptr<Tiles>>& tiles);

    sf::Sprite getSprite() const;
    std::vector<Projectile>& getProj();
    sf::Sprite getProjShape(Projectile& proj) const;
    
    float x, y;
    int life = 3;

    ennemyState currentState;
    Assets assets;
    sf::Clock rangedAttackClock;
    sf::Clock takeDamageClock;
    sf::Clock rangClock;

    std::vector<Projectile> projectiles;
    std::vector<sf::Sprite> spritEnnemies;
    sf::Vector2f moveForCol;

    size_t pathIndex;
    sf::CircleShape circle;


protected : 

    float radiusDetection; 
    float speed;
    float gravity;
    float velocityY;
    float maxFallSpeed = 800;
    float boxCol1;
    float boxCol2;

    bool stop = false;
    bool isWakable = true;
    bool onTheGround = false;
    bool inWalk = false;

    
    float scaleEnnemy = 1;
    bool lastDepIsLeft;

    sf::Sprite spriteEnnemy;

    Animation attackAnim, walkAnim, walkAnimR, standAnim, hitAnim, hitAnimR, attackAnimR;
};

#endif
