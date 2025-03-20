#include "MainMenu.hpp"
#include <iostream>

void MainMenu::initButtons() {
    buttons.emplace_back(1, "Jouer", "Jouer", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(2, "Options", "Options", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(3, "Quitter", "Quitter", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 400), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(4, "Editeur", "Editeur", Shared::font, sf::Vector2f(50, 50), sf::Vector2f(200, 50), []() {});
}

MainMenu::MainMenu() : Menu() {
    initButtons();
}

int MainMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    return Menu::handleInput(window, event);
}