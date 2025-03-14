#include "texture_loader.hpp"
#include <iostream>
#include <string>

TextureLoader::TextureLoader()
{
    for (const auto& file : std::filesystem::directory_iterator("./assets/images"))
    {
        if (file.is_regular_file())
        {
            const std::string filePath = file.path().string();
            sf::Texture       texture;

            if (!texture.loadFromFile(filePath)) { throw std::runtime_error("Failed to load texture!"); }

            texture.setSmooth(true);
            textures[file.path().filename().string()] = texture;
        }
    }
}

sf::Texture& TextureLoader::getTexture(const std::string& textureName)
{
    auto it = textures.find(textureName);
    if (it == textures.end()) { std::runtime_error("Texture not found!"); }
    return it->second;
}