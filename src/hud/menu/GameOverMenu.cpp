#include "gameOverMenu.hpp"
#include <iostream>

GameOverMenu::GameOverMenu() {
    if (!font.loadFromFile("assets/fonts/Ethnocentric Rg.otf")) {
        std::cerr << "Error loading font! : arial.ttf" << std::endl;
    }

    background.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
    background.setFillColor(sf::Color::Black);

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(static_cast<float>(Config::WINDOW_WIDTH) / 2.f - gameOverText.getLocalBounds().width / 2.f, static_cast<float>(Config::WINDOW_HEIGHT) / 3.f);

    pressKeyText.setFont(font);
    pressKeyText.setString("Appuyez sur une touche pour continuer");
    pressKeyText.setCharacterSize(30);
    pressKeyText.setFillColor(sf::Color::White);
    pressKeyText.setPosition(static_cast<float>(Config::WINDOW_WIDTH) / 2.f - pressKeyText.getLocalBounds().width / 2.f,static_cast<float>(Config::WINDOW_HEIGHT) / 2.f + 50.f);
}

void GameOverMenu::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(gameOverText);
    window.draw(pressKeyText);
}

bool GameOverMenu::handleInput() {
    // Vérifier les touches du clavier
    for (int i = sf::Keyboard::Key::A; i <= sf::Keyboard::Key::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
            return true;
        }
    }

    // Vérifier les boutons de la souris
    for (int i = sf::Mouse::Left; i <= sf::Mouse::ButtonCount; ++i) {
        if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i))) {
            return true;
        }
    }

    // Vérifier les boutons de la manette (supporte une seule manette ici)
    for (unsigned int joystickId = 0; joystickId < sf::Joystick::Count; ++joystickId) {
        if (sf::Joystick::isConnected(joystickId)) {
            for (unsigned int button = 0; button < sf::Joystick::getButtonCount(joystickId); ++button) {
                if (sf::Joystick::isButtonPressed(joystickId, button)) {
                    return true;
                }
            }

            // Vérifier si un axe de la manette est déplacé
            for (int axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
                if (std::abs(sf::Joystick::getAxisPosition(joystickId, static_cast<sf::Joystick::Axis>(axis))) > 50) {
                    return true;
                }
            }
        }
    }

    return false;
}