#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <list>
#include <unordered_map>
#include <memory>

class SoundManager
{
public:
    SoundManager();

    void playSound(const std::string& name);

    void update();

private:
    std::unordered_map<std::string, sf::SoundBuffer> buffers;
    std::list<std::unique_ptr<sf::Sound>>            activeSounds;
};