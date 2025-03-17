#include "SoundMenu.hpp"
#include <iostream>

SoundMenu::SoundMenu() : Menu() {
    initButtons();
    initSliders();
}

SoundMenu::~SoundMenu() {
    delete mainVolumeSlider;
    delete musicVolumeSlider;
    delete sfxVolumeSlider;
}

void SoundMenu::initButtons() {
    buttons.emplace_back(1, "Retour", "Retour", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {});
}

void SoundMenu::initSliders() {
    mainVolumeSlider = new Slider(static_cast<int>((Config::WINDOW_WIDTH - 400) / 2.f), 300, 400, 0, 100, font, "Volume Principal", 100);
    musicVolumeSlider = new Slider(static_cast<int>((Config::WINDOW_WIDTH - 400) / 2.f), 400, 400, 0, 100, font, "Volume Musique", 100);
    sfxVolumeSlider = new Slider(static_cast<int>((Config::WINDOW_WIDTH - 400) / 2.f), 500, 400, 0, 100, font, "Volume SFX", 100);
}

int SoundMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    mainVolumeSlider->handleInput(window, event);
    musicVolumeSlider->handleInput(window, event);
    sfxVolumeSlider->handleInput(window, event);

    updateSliderValues();

    return Menu::handleInput(window, event);
}

void SoundMenu::renderSliders(sf::RenderWindow& window) {
    mainVolumeSlider->render(window);
    musicVolumeSlider->render(window);
    sfxVolumeSlider->render(window);
}

void SoundMenu::updateSliderValues() {
    int mainVolume = static_cast<int>(mainVolumeSlider->getValue());
    int musicVolume = static_cast<int>(musicVolumeSlider->getValue());
    int sfxVolume = static_cast<int>(sfxVolumeSlider->getValue());

    audioSystem.setMainVolume(static_cast<float>(mainVolume));
    audioSystem.setMusicVolume(static_cast<float>(musicVolume));
    audioSystem.setSFXVolume(static_cast<float>(sfxVolume));
}
