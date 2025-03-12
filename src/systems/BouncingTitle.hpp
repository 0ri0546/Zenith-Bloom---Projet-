#ifndef BOUNCING_TITLE_HPP
#define BOUNCING_TITLE_HPP

#include "Datas.hpp"

class BouncingTitle {
public:
    BouncingTitle(const std::string& title, sf::Font& font);
    void update(float deltaTime);
    void handleInput(bool& gameStarted);
    void draw(sf::RenderWindow& window);

private:
    sf::Text titleText, pressKeyText;
    sf::Text instructionText;
    float velocityY = 0.f;
    float gravity = 980.f;
    float bounceDamping = 0.7f;
    bool isWaitingForInput = false;
    bool showInstruction = false;
    float instructionAlpha = 0.f;
    sf::Clock timer, blinkingTimer;
};

#endif 
