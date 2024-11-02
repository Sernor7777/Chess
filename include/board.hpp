#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <map>
#include <memory>

#include "bitboard.hpp"
#include "piece.hpp"
#include "texture_loader.hpp"
#include "move.hpp"

enum BitboardTypes
{
    OccupiedByWhite = 12,
    OccupiedByBlack,
    Occupied,
    AttackedByWhite,
    AttackedByBlack
};

class Board
{
public:
    Board(TextureLoader& textureLoader);
    // ~Board();
    // Board(std::string FEN);

    void makeMove(int fromFile, int fromRank, int toFile, int toRank, PieceTypes pieceType);
    void readFEN(const std::string& FEN);
    void displayBoard(sf::RenderWindow& window, TextureLoader& textureLoader);
    void handleInput(sf::RenderWindow& window, sf::Event& event);
    // std::vector<Move> getLegalMoves();
    // SquareStatus getSquareStatus(int rank, int file, bool isWhite);

    std::array<Bitboard, 17>& getBitboards();

private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> boardOLD;
    std::array<std::unique_ptr<Piece>, 64> board;
    std::array<Bitboard, 17> bitboards;
    Piece* draggedPiece = nullptr;
    TextureLoader textureLoader;

    void setupBoard();
    void drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite);
};