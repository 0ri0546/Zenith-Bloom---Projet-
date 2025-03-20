#include "LevelSelectorMenu.hpp"

LevelSelectMenu::LevelSelectMenu() {
    initButtons();
}

void LevelSelectMenu::initButtons() {
    buttons.emplace_back(1, "Retour", "Retour", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(2, "Level Tuto", "Level Tuto", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 300) / 2.f, 300), sf::Vector2f(300.f, 50.f), []() {});

    buttons.emplace_back(2, "Level 1", "Level 1", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 300) / 2.f, 400), sf::Vector2f(300.f, 50.f), []() {});
}

int LevelSelectMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    return Menu::handleInput(window, event);
}