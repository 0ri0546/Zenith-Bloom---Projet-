#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
//#include "../entities/FSM.hpp"

class Projectile {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::Vector2f velocityForWater;
    float speed;
    float speedForWater;
    bool goingLeft;

    float velocityY;
    float gravity;
    float gravityForWater;
    float rotationSpeed = 5.0f;

public:
    Projectile(sf::Texture& texture, sf::Vector2f position, bool goingLeft);
    ~Projectile();
    void update(float deltaTime);
    void updateForWater(float deltaTime);
    //void updateShootEnnemy(float deltaTime, vector<Ennemy>& ennemie);
    sf::FloatRect getBounds() const;
    sf::Sprite getSprite() const;
    bool returnGoing();
    void resize(float width, float height);

};

#endif
