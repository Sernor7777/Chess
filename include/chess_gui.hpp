#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "engine.hpp"
#include "texture_loader.hpp"
#include "sound_manager.hpp"
#include "types.hpp"

class ChessGUI
{
public:
    ChessGUI(Engine& engine);
    ~ChessGUI() = default;

    void run();

    void drawBoard(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, sf::Event& event);

private:
    sf::RenderWindow  window;
    Engine            engine;
    sf::Sprite        sprite;
    std::vector<Move> legalMoves;
    TextureLoader     textureLoader;
    SoundManager      soundManager;
    Square            draggedPieceIndex = SQ_NONE;

    void setPieceSprite(Piece piece);
};
