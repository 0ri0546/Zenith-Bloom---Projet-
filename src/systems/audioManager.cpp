
#include "../systems/audioManager.hpp"
#include <iostream>

AudioManager::AudioManager() {
    loadAllSounds(); // Charge tous les sons automatiquement
}

AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::loadAllSounds() {
    loadSound("tirIcend", "assets/sound/tirIcend.wav");
    loadSound("tir", "assets/sound/tir.mp3");
    loadSound("lv1", "assets/sound/FlowLV1.wav");
    loadSound("tirE", "assets/sound/tirE.wav");
    loadSound("hit1", "assets/sound/hit1.wav");
    loadSound("explo", "assets/sound/explo.wav");
    
}

void AudioManager::loadSound(const std::string& name, const std::string& filename) {
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filename)) {
        std::cerr << "Erreur: ompossible de charger le son " << filename << std::endl;
        return;
    }
    soundBuffers[name] = std::move(buffer);
    sounds[name] = std::make_unique<sf::Sound>(*soundBuffers[name]);
}

void AudioManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name]->play();
    }
    else {
        std::cerr << "erreur: Son " << name << " non chargé." << std::endl;
    }
}

void AudioManager::stopSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name]->stop();
    }
}

void AudioManager::stopAllSounds() {
    for (auto& pair : sounds) {
        pair.second->stop();
    }
}

void AudioManager::setSoundVolume(const std::string& name, float volume) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name]->setVolume(volume);
    }
    else {
        std::cerr << "Erreur: Son " << name << " non chargé." << std::endl;
    }
}

void AudioManager::setSoundLoop(const std::string& name, bool loop) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name]->setLoop(loop);
    }
    else {
        std::cerr << "Erreur: Son " << name << " non chargé." << std::endl;
    }
}
