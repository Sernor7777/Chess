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
#include "magic_bitboard.hpp"

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
    Board(TextureLoader& textureLoader, MagicBitboard& magicBitboard);
    // ~Board();
    // Board(std::string FEN);

    //void makeMove(int fromFile, int fromRank, int toFile, int toRank, PieceTypes pieceType);
    void makeMove(Move move, PieceTypes pieceType);
    void readFEN(const std::string& FEN);
    void displayBoard(sf::RenderWindow& window, TextureLoader& textureLoader);
    void handleInput(sf::RenderWindow& window, sf::Event& event);
    std::array<uint64_t, 64>& getRookMagicNumbers();
    std::array<uint64_t, 64>& getBishopMagicNumbers();
    // std::vector<Move> getLegalMoves();
    // SquareStatus getSquareStatus(int rank, int file, bool isWhite);

    std::array<Bitboard, 17>& getBitboards();

private:
    std::array<std::unique_ptr<Piece>, 64> board;
    std::array<Bitboard, 17> bitboards;
    Piece* draggedPiece = nullptr;
    std::vector<Move> legalMoves;
    TextureLoader textureLoader;
    MagicBitboard magicBitboard;

    void setupBoard();
    void drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite);
};