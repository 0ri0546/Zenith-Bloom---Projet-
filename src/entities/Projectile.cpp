#include "Projectile.hpp"

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, bool goingLeft) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    speed = 1300.0f;
    velocity.x = goingLeft ? -speed : speed;

    velocityY = -200.0f;
    gravity = 500.0f;
}

void Projectile::update(float deltaTime) {
    velocityY += gravity * deltaTime;
    sprite.move(velocity.x * deltaTime, velocityY * deltaTime);
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

Projectile::~Projectile() {}