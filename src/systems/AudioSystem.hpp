#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <SFML/Audio.hpp>

class AudioSystem {
private:
    sf::Music music;
    sf::SoundBuffer sfxBuffer;
    sf::Sound sfx;

public:
    AudioSystem();

    void setMainVolume(float volume);
    void setMusicVolume(float volume);
    void setSFXVolume(float volume);

    void playMusic(const std::string& musicFile);
    void playSFX(const std::string& sfxFile);
};

#endif // AUDIOSYSTEM_HPP