#include "SoundMenu.hpp"
#include <iostream>

SoundMenu::SoundMenu() : Menu() {
    initButtons();
}

void SoundMenu::initButtons() {
    buttons.emplace_back(1, "Retour", "Retour", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});

    buttons.emplace_back(2, "Volume Principal", "Volume Principal", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 400) / 2.f, 350), sf::Vector2f(400, 5), []() {}, 0, 100, 100, true);
    buttons.emplace_back(3, "Volume Musique", "Volume Musique", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 400) / 2.f, 500), sf::Vector2f(400, 5), []() {}, 0, 100, 100, true);
    buttons.emplace_back(4, "Volume SFX", "Volume SFX", Shared::font, sf::Vector2f((Config::WINDOW_WIDTH - 400) / 2.f, 650), sf::Vector2f(400, 5), []() {}, 0, 100, 100, true);
}

int SoundMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool sliderInteracted = false;

    for (auto& button : buttons) {
        if (button.getIsSlider()) {
            int buttonResult = button.handleInput(mousePos, event);

            if (buttonResult != 0) {
                sliderInteracted = true;
                updateSliderValues();
                break;
            }
        }
    }

    if (!sliderInteracted) {
        for (auto& button : buttons) {
            int buttonResult = button.handleInput(mousePos, event);

            if (buttonResult != 0 && &button != &buttons[0]) {
                updateSliderValues();
                return buttonResult;
            }
        }
    }

    return Menu::handleInput(window, event);
}

void SoundMenu::updateSliderValues() {
    int mainVolume = static_cast<int>(buttons[1].getValue());
    int musicVolume = static_cast<int>(buttons[2].getValue());
    int sfxVolume = static_cast<int>(buttons[3].getValue());

    audioSystem.setMainVolume(static_cast<float>(mainVolume));
    audioSystem.setMusicVolume(static_cast<float>(musicVolume));
    audioSystem.setSFXVolume(static_cast<float>(sfxVolume));
}
