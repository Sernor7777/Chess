#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include <map>

#include "config.hpp"

class TextureLoader
{
public:
    TextureLoader();

    sf::Texture& getTexture(const char* textureName);

private:
    std::map<std::string, sf::Texture> textures;
};