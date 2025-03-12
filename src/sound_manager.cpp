#include "sound_manager.hpp"

#include <filesystem>

#include "config.hpp"

SoundManager::SoundManager()
{
    for (const auto& file : std::filesystem::directory_iterator("./assets/sounds"))
    {
        if (file.is_regular_file())
        {
            const std::string fileName = file.path().filename().string();
            if (!buffers[fileName].loadFromFile(file.path().string())) { throw std::runtime_error("Failed to load sound!"); }
        }
    }
}

void SoundManager::playSound(const std::string& name)
{
    std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();
    sound->setBuffer(buffers[name]);
    sound->play();
    activeSounds.push_back(std::move(sound));
}

void SoundManager::update()
{
    activeSounds.remove_if([](std::unique_ptr<sf::Sound>& sound) { return sound->getStatus() == sf::Sound::Stopped; });
}