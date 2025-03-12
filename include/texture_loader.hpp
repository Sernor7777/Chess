#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <unordered_map>

#include "config.hpp"

class TextureLoader
{
public:
    TextureLoader();

    sf::Texture& getTexture(const std::string& textureName);

private:
    std::unordered_map<std::string, sf::Texture> textures;
};