#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../systems/Datas.hpp"

class Projectile {
public:
    // constructeur et destructeur
    Projectile(sf::Texture& texture, sf::Vector2f position, bool goingLeft);
    ~Projectile();

    // void
    void update(float deltaTime);
    void updateForWater(float deltaTime);
    void updateForDrone(float deltaTime);
    void resize(float width, float height);

    // getters 
    sf::FloatRect getBounds() const;
    sf::Sprite getSprite() const;
    bool returnGoing();

private:
    sf::Sprite sprite;

    sf::Vector2f velocity;
    sf::Vector2f velocityForWater;
    sf::Vector2f velocityForDrone;

    float speed;
    float speedForWater;
    float speedForDrone;
    float velocityY;
    float gravity;
    float gravityForWater;
    float gravityForDrone;
    float rotationSpeed;

    bool goingLeft;
};

#endif
