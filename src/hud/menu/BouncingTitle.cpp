#include "BouncingTitle.hpp"

BouncingTitle::BouncingTitle(const std::string& title, sf::Font& font) {
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(130);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(5);

    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    titleText.setPosition(Config::WINDOW_WIDTH / 2, -textBounds.height);

    instructionText.setFont(font); //text du studio
    instructionText.setString("By SolarSeed Studio");
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(sf::Color(255, 255, 255, 0));
    instructionText.setStyle(sf::Text::Bold);
    instructionText.setOutlineColor(sf::Color::Black);
    instructionText.setOutlineThickness(4);
    sf::FloatRect instrBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
    instructionText.setPosition(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT * 3 / 4);

    sf::FloatRect pressKeyBounds = pressKeyText.getLocalBounds(); // text press A/Enter
    pressKeyText.setOrigin(pressKeyBounds.width / 2, pressKeyBounds.height / 2);
    pressKeyText.setFont(font);
    pressKeyText.setCharacterSize(50);
    pressKeyText.setFillColor(sf::Color::White);
    pressKeyText.setStyle(sf::Text::Bold);
    pressKeyText.setRotation(-20);
    pressKeyText.setOutlineColor(sf::Color::Black);
    pressKeyText.setOutlineThickness(4);
    pressKeyText.setPosition(textBounds.width + 20, Config::WINDOW_HEIGHT / 2 + 40);

    timer.restart();
    blinkingTimer.restart();
}

void BouncingTitle::initBackground() {
    backgroundSprite.setTexture(Shared::backgroundTexture);
    backgroundSprite.setScale(1.23f, 1.23f);
    backgroundSprite.setPosition((Config::WINDOW_WIDTH - backgroundSprite.getGlobalBounds().width) / 2.f, 0.f);
}

void BouncingTitle::update(float deltaTime) {
    initBackground();
    if (!isWaitingForInput) {
        velocityY += gravity * deltaTime;
        titleText.move(0, velocityY * deltaTime);

        if (titleText.getPosition().y >= Config::WINDOW_HEIGHT / 2.5) {
            titleText.setPosition(titleText.getPosition().x, Config::WINDOW_HEIGHT / 2.5);
            velocityY = -velocityY * bounceDamping;

            if (std::abs(velocityY) < 10.0f) {
                velocityY = 0;
                isWaitingForInput = true;
                timer.restart(); //text du studio
            }
        }
    }

    if (isWaitingForInput && timer.getElapsedTime().asSeconds() > 0.5f) { //text du studio
        showInstruction = true;
    }

    if (showInstruction && instructionAlpha < 255) { //text du studio : fondu
        instructionAlpha += 255 * deltaTime;
        if (instructionAlpha > 255) instructionAlpha = 255;
        instructionText.setFillColor(sf::Color(255, 255, 255, instructionAlpha));
    }

    if (isWaitingForInput && timer.getElapsedTime().asSeconds() > 2.0f) { // text press A/Enter
        if (sf::Joystick::isConnected(0)) {
            pressKeyText.setString("Press A");
        }
        else {
            pressKeyText.setString("Press Enter");
        }

        if (blinkingTimer.getElapsedTime().asSeconds() > 0.5f) { // text press A/Enter : clignotement
            float alpha = pressKeyText.getFillColor().a == 255 ? 0 : 255;
            pressKeyText.setFillColor(sf::Color(255, 255, 255, alpha));
            pressKeyText.setOutlineColor(sf::Color(0, 0, 0, alpha));
            canSkip = true;
            blinkingTimer.restart();
        }
    }
}

void BouncingTitle::handleInput(bool& gameStarted) {
    if (canSkip && (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
        (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0,0)))) {
        gameStarted = true;
    }
}

void BouncingTitle::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(titleText);
    if (showInstruction) {
        window.draw(instructionText);
    }
    if (timer.getElapsedTime().asSeconds() > 2.0f) {
        window.draw(pressKeyText);
    }

}

bool BouncingTitle::fallingText(float deltaTime) {
    velocityY += gravity * deltaTime;
    titleText.move(0, velocityY * deltaTime);
    instructionText.move(0, velocityY * deltaTime);
    pressKeyText.move(0, velocityY * deltaTime);

    if (titleText.getPosition().y >= Config::WINDOW_HEIGHT + 100) {
        titleText.setPosition(0, 1200);
        instructionText.move(0, 1200);
        pressKeyText.move(0, 1200);
        return true;
    }
    return false;
}
