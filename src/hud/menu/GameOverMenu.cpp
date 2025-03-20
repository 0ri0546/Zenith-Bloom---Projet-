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
    gameOverText.setPosition(Config::WINDOW_WIDTH / 2.f - gameOverText.getLocalBounds().width / 2.f, Config::WINDOW_HEIGHT / 3.f);

    pressKeyText.setFont(font);
    pressKeyText.setString("Appuyez sur une touche pour continuer");
    pressKeyText.setCharacterSize(30);
    pressKeyText.setFillColor(sf::Color::White);
    pressKeyText.setPosition(Config::WINDOW_WIDTH / 2.f - pressKeyText.getLocalBounds().width / 2.f, Config::WINDOW_HEIGHT / 2.f + 50);
}

void GameOverMenu::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(gameOverText);
    window.draw(pressKeyText);
}

bool GameOverMenu::handleInput() {
    for (int i = sf::Keyboard::Key::A; i <= sf::Keyboard::Key::BackSlash; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
            return true;
        }
    }
    return false;
}
