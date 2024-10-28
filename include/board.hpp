#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <map>
#include <memory>
#include "piece.hpp"
#include "texture_loader.hpp"

enum SquareStatus {
    Empty,
    Friendly,
    Enemy
};

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
    SquareStatus getSquareStatus(int rank, int file, bool isWhite);

private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    Piece* draggedPiece = nullptr;
    TextureLoader textureLoader;

    void setupBoard();
    // bool verifyValidMove(int startSquare, int endSquare);
    void drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite);
};