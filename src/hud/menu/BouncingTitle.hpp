#ifndef BOUNCING_TITLE_HPP
#define BOUNCING_TITLE_HPP

#include "../../systems/Datas.hpp"

class BouncingTitle {
public:
    // constructeur
    BouncingTitle(const std::string& title, sf::Font& font);

    //void
    void update(float deltaTime);
    void handleInput(bool& gameStarted);
    void draw(sf::RenderWindow& window);

    // autres methodes
    bool fallingText(float deltaTime);

    // variables
    bool canSkip = false;
    void initBackground();

private:
    sf::Clock timer, blinkingTimer;
    sf::Sprite backgroundSprite;
    sf::Text titleText, instructionText, pressKeyText;

    float velocityY = 0.f;
    float gravity = 980.f;
    float bounceDamping = 0.5f;
    float instructionAlpha = 0.f;

    bool isWaitingForInput = false;
    bool showInstruction = false;
};

#endif 
