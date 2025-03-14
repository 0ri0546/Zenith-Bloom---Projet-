#include "VideoMenu.hpp"
#include <iostream>

void VideoMenu::initButtons() {
    buttons.emplace_back(1, "Retour", "Retour", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(2, "Plein Ecran", "Plein Ecran", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(3, "Synchronisation Vertical - ON", "Synchronisation Vertical - ON", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 400), sf::Vector2f(200, 50), []() {});

    fpsSlider = new Slider((Config::WINDOW_WIDTH - 400) / 2.f, 530, 400, 20, 30, 240, font, "Max FPS : ", 60);
}

VideoMenu::VideoMenu(MenuList lastMenu) : Menu(), isFullscreen(true), isVSync(true), lastMenu(lastMenu) {
    initButtons();
}

VideoMenu::~VideoMenu() {
    delete fpsSlider;
}

int VideoMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    fpsSlider->handleInput(window, event);
    int currentFPS = fpsSlider->getValue();
    window.setFramerateLimit(currentFPS);
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

void VideoMenu::toggleVSync(sf::RenderWindow& window) {
    isVSync = !isVSync;
    if (isVSync) {
        window.setVerticalSyncEnabled(true);
        buttons[2].setText("Synchronisation Vertical - ON");
    }
    else {
        window.setVerticalSyncEnabled(false);
        buttons[2].setText("Synchronisation Vertical - OFF");
    }
}

void VideoMenu::renderSlider(sf::RenderWindow& window) {
    fpsSlider->render(window);
}