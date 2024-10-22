#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <map>
#include <memory>
#include "piece.hpp"
#include "texture_loader.hpp"

class Board
{
public:
    Board(TextureLoader& textureLoader);
    // ~Board();
    // Board(std::string FEN);

    void makeMove(int startSquare, int endSquare);
    void readFEN(const std::string& FEN);
    void displayBoard(sf::RenderWindow& window, TextureLoader& textureLoader);
    void handleInput(sf::RenderWindow& window, sf::Event& event);
    std::vector<Move> getLegalMoves();

private:
    std::array<std::array<char, 8>, 8> boardOLD;
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    std::map<std::string, sf::Texture> pieceTextures;
    std::map<std::string, sf::Sprite> pieceSprites;
    const std::string pieceTypes[12] = { "wp", "wr", "wn", "wb", "wq", "wk", "bp", "br", "bn", "bb", "bq", "bk" };
    std::map<char, std::string> pieceNames = {
        {'P', "wp"}, {'N', "wn"}, {'B', "wb"}, {'R', "wr"}, {'Q', "wq"}, {'K', "wk"},
        {'p', "bp"}, {'n', "bn"}, {'b', "bb"}, {'r', "br"}, {'q', "bq"}, {'k', "bk"}
    };

    TextureLoader textureLoader;

    void setupBoard();
    // bool verifyValidMove(int startSquare, int endSquare);
    void drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite);
};