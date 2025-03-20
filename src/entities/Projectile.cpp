#include "Projectile.hpp"

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, bool goingLeft) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    speed = 1100.0f;
    speedForWater = 200.0f;
    velocity.x = goingLeft ? -speed : speed;
    velocityForWater.x = goingLeft ? -speedForWater : speedForWater;

    velocityY = -200.0f;
    gravity = 500.0f;
    gravityForWater = 1000.f;
    goingLeft = false;
    rotationSpeed = 5.0f;
}

void Projectile::update(float deltaTime) {
    velocityY += gravity * deltaTime;
    sprite.move(velocity.x * deltaTime, velocityY * deltaTime);
    float angle = std::atan2(velocityY, velocity.x) * 180.f / 3.14159f;
    sprite.setRotation(angle);
}

void Projectile::updateForWater(float deltaTime) {
    velocityY += gravityForWater * deltaTime;
    sprite.move(velocityForWater.x * deltaTime, velocityY * deltaTime);
    float angle = std::atan2(velocityY, velocity.x) * 180.f / 3.14159f;
    sprite.setRotation(angle);
}

//void Projectile::updateShootEnnemy(float deltaTime, vector<Ennemy>& ennemie)
//{
//    for (auto ennemy : ennemie) {
//        sprite.move(ennemy.getSprite().getPosition().x, ennemy.getSprite().getPosition().x);
//    }
//}

void Projectile::resize(float width, float height) {
    sprite.setScale(width / sprite.getGlobalBounds().width, height / sprite.getGlobalBounds().height);
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Sprite Projectile::getSprite() const {
    return sprite;
}

bool Projectile::returnGoing()
{
    return goingLeft;
}

Projectile::~Projectile() {}