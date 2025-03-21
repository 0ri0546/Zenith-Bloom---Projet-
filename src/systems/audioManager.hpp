#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

class AudioManager {
public:
    static AudioManager& getInstance();

    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void stopAllSounds();

    void setSoundVolume(const std::string& name, float volume);
    void setSoundLoop(const std::string& name, bool loop);

private:
    AudioManager();
    ~AudioManager() = default;
    void loadAllSounds();
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
    std::unordered_map<std::string, std::unique_ptr<sf::Sound>> sounds;
};

#endif
