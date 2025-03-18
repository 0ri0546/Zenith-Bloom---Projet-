#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Datas.hpp"

class Animation {
public:
    Animation(sf::Texture& texture, int frameWidth, int frameHeight, int numFrames, float switchTime);

    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite, int row);
    void takeSecondImage(sf::Sprite& sprite, int row);

private:
    sf::Texture& texture;
    int frameWidth, frameHeight;
    int numFrames, currentFrame;
    float switchTime, elapsedTime;
};

#endif
