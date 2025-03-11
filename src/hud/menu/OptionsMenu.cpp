#include "OptionsMenu.hpp"
#include <iostream>

void OptionsMenu::initButtons() {
    buttons.emplace_back(1, "Retour", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(2, "Video", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(3, "Son", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 400), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(4, "Controles", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 500), sf::Vector2f(200, 50), []() {});
}

OptionsMenu::OptionsMenu(MenuList lastMenu) : Menu(), lastMenu(lastMenu) {
    initButtons();
}
int OptionsMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    return Menu::handleInput(window, event);
}