
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
    loadSound("tir", "assets/sound/tir.MP3");
    /*loadSound("jump", "assets/jump.wav");
    loadSound("damage", "assets/damage.wav");*/
    
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
