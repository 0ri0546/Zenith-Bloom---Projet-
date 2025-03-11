#include "Menu.hpp"
#include <iostream>

void Menu::initFont() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error loading font! : arial.ttf" << std::endl;
    }
}

void Menu::initBackground() {
    if (!backgroundTexture.loadFromFile("assets/textures/menu/background.png")) {
        std::cerr << "Error loading texture! : background.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

Menu::Menu() {
    initFont();
    initBackground();
}

int Menu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& button : buttons) {
            int buttonResult = button.handleMouseClick(mousePos);
            if (buttonResult != 0) {
                return buttonResult;
            }
        }
    }

    for (auto& button : buttons) {
        button.handleMouseHover(mousePos);
    }

    return 0;
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& button : buttons) {
        button.render(window);
    }
}