#include "VideoMenu.hpp"
#include <iostream>

void VideoMenu::initButtons() {
    buttons.emplace_back(1, "Retour", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(2, "Plein Ecran", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(2, "Plein Ecran", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(2, "Plein Ecran", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});
}

VideoMenu::VideoMenu() : Menu(), isFullscreen(true), currentResolution(1920, 1080) {
    initButtons();
}
int VideoMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    return Menu::handleInput(window, event);
}

void VideoMenu::toggleFullscreen(sf::RenderWindow& window) {
    isFullscreen = !isFullscreen;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    if (isFullscreen) {
        window.create(desktopMode, "Zenith Bloom", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Zenith Bloom", sf::Style::Close);
    }
}