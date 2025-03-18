#include "Animation.hpp"

Animation::Animation(sf::Texture& texture, int frameWidth, int frameHeight, int numFrames, float switchTime)
    : texture(texture), frameWidth(frameWidth), frameHeight(frameHeight), numFrames(numFrames), switchTime(switchTime) {
    currentFrame = 0;
    elapsedTime = 0.f;
}

void Animation::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= switchTime) {
        elapsedTime -= switchTime;
        currentFrame = (currentFrame + 1) % numFrames;
    }
}

void Animation::applyToSprite(sf::Sprite& sprite, int row) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, row * frameHeight, frameWidth, frameHeight));
    sprite.setScale(100.f / frameWidth, 100.f / frameHeight);
}
