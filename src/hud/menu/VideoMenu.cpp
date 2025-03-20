#include "VideoMenu.hpp"
#include <iostream>

void VideoMenu::initButtons() {
    buttons.emplace_back(1, "Retour", "Retour", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(2, "Plein Ecran", "Plein Ecran", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {});
    buttons.emplace_back(3, "Synchronisation Vertical - ON", "Synchronisation Vertical - ON", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 400) / 2.f, 400), sf::Vector2f(400, 50), []() {});

    buttons.emplace_back(4, "Max FPS : ", "Max FPS : ", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 400) / 2.f, 530), sf::Vector2f(400, 5), []() {}, 30, 240, 60, true);
}

VideoMenu::VideoMenu(MenuList lastMenu) : Menu(), isFullscreen(true), isVSync(true), lastMenu(lastMenu) {
    initButtons();
}

int VideoMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool sliderInteracted = false;

    for (auto& button : buttons) {
        if (button.getIsSlider()) {
            int buttonResult = button.handleInput(mousePos, event);

            if (buttonResult != 0) {
                sliderInteracted = true;
                int currentFPS = buttons[3].getValue();
                window.setFramerateLimit(currentFPS);
                break;
            }
        }
    }

    if (!sliderInteracted) {
        for (auto& button : buttons) {
            int buttonResult = button.handleInput(mousePos, event);

            if (buttonResult != 0 && &button == &buttons[3]) {
                int currentFPS = buttons[3].getValue();
                window.setFramerateLimit(currentFPS);
                return buttonResult;
            }
        }
    }

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

void VideoMenu::update(sf::RenderWindow& window) {
    int currentFPS = buttons[3].getValue();
    window.setFramerateLimit(currentFPS);
}