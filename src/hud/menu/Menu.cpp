#include "Menu.hpp"
#include <iostream>

void Menu::initBackground() {
    backgroundSprite.setTexture(Shared::backgroundTexture);
    backgroundSprite.setScale(1.23f, 1.23f);
    backgroundSprite.setPosition((Config::WINDOW_WIDTH - backgroundSprite.getGlobalBounds().width) / 2.f, 0.f);
}

Menu::Menu() {
    initBackground();

    isGamepadConnected = sf::Joystick::isConnected(0);

    if (isGamepadConnected && !buttons.empty()) {
        currentHoveredButtonIndex = 0;
        updateHoverForButton(currentHoveredButtonIndex);
    }
}

void Menu::updateHoverForButton(int index) {
    if (buttons.empty() || index < 0 || index >= static_cast<int>(buttons.size())) {
        return;
    }

    static int lastHoveredIndex = -1;

    if (index == lastHoveredIndex) {
        return;
    }

    lastHoveredIndex = index;

    for (size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getIsSlider()) {
            buttons[i].setHoverSlider(false);
        }
        else {
            buttons[i].setHoverButton(false);
        }
    }

    if (buttons[index].getIsSlider()) {
        buttons[index].setHoverSlider(true);
    }
    else {
        buttons[index].setHoverButton(true);
    }
}


int Menu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    static sf::Clock clickClock;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    bool wasGamepadConnected = isGamepadConnected;
    isGamepadConnected = sf::Joystick::isConnected(0);

    if (isGamepadConnected && !wasGamepadConnected && !buttons.empty()) {
        currentHoveredButtonIndex = 0;
        updateHoverForButton(currentHoveredButtonIndex);
    }

    if (isGamepadConnected) {
        updateHoverWithGamepad();

        if (sf::Joystick::isButtonPressed(0, 0) && clickClock.getElapsedTime().asMilliseconds() > 300) {
            if (!buttons.empty() && currentHoveredButtonIndex >= 0 && currentHoveredButtonIndex < buttons.size()) {
                int buttonResult = buttons[currentHoveredButtonIndex].handleInput(mousePos, event, true);
                clickClock.restart();
                return buttonResult;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (clickClock.getElapsedTime().asMilliseconds() > 300) {
            for (auto& button : buttons) {
                int buttonResult = button.handleInput(mousePos, event);
                if (buttonResult != 0) {
                    clickClock.restart();
                    return buttonResult;
                }
            }
        }
    }

    for (auto& button : buttons) {
        button.handleMouseHover(mousePos);
    }

    return 0;
}

void Menu::updateHoverWithGamepad() {
    static sf::Clock clock;
    float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    if (clock.getElapsedTime().asMilliseconds() > 200) {
        if (std::abs(yAxis) > 50) {
            int direction = (yAxis > 0) ? 1 : -1;

            int newIndex = currentHoveredButtonIndex + direction;
            newIndex = std::clamp(newIndex, 0, static_cast<int>(buttons.size() - 1));

            if (newIndex != currentHoveredButtonIndex) {
                currentHoveredButtonIndex = newIndex;
                updateHoverForButton(currentHoveredButtonIndex);
            }

            clock.restart();
        }
    }

    if (currentHoveredButtonIndex >= 0 && currentHoveredButtonIndex < buttons.size() && buttons[currentHoveredButtonIndex].getIsSlider()) {
        buttons[currentHoveredButtonIndex].adjustSliderValue(xAxis);
    }

    if (clock.getElapsedTime().asMilliseconds() > 200) {
        float povY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

        int newIndex = currentHoveredButtonIndex;
        if (povY > 50) { // D-Pad down
            newIndex--;
            newIndex = std::clamp(newIndex, 0, static_cast<int>(buttons.size() - 1));
        }
        else if (povY < -50) { // D-Pad up
            newIndex++;
            newIndex = std::clamp(newIndex, 0, static_cast<int>(buttons.size() - 1));
        }

        if (newIndex != currentHoveredButtonIndex) {
            currentHoveredButtonIndex = newIndex;
            updateHoverForButton(currentHoveredButtonIndex);
            clock.restart();
        }
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& button : buttons) {
        button.render(window);
    }
}