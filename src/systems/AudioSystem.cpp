#include "AudioSystem.hpp"
#include <iostream>

AudioSystem::AudioSystem() {}

void AudioSystem::setMainVolume(float volume) {
    music.setVolume(volume);
    sfx.setVolume(volume);
}

void AudioSystem::setMusicVolume(float volume) {
    music.setVolume(volume);
}

void AudioSystem::setSFXVolume(float volume) {
    sfx.setVolume(volume);
}

void AudioSystem::playMusic(const std::string& musicFile) {
    if (!music.openFromFile(musicFile)) {
        std::cerr << "Erreur lors du chargement de la musique" << std::endl;
    }
    music.play();
}

void AudioSystem::playSFX(const std::string& sfxFile) {
    if (!sfxBuffer.loadFromFile(sfxFile)) {
        std::cerr << "Erreur lors du chargement de l'effet sonore" << std::endl;
    }
    sfx.setBuffer(sfxBuffer);
    sfx.play();
}