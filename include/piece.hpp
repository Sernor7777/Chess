#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "texture_loader.hpp"
#include "bitboard.hpp"
#include "movegen.hpp"
#include "move.hpp"

class Board;

enum PieceTypes
{
    WhitePawn,
    WhiteRook,
    WhiteKnight,
    WhiteBishop,
    WhiteQueen,
    WhiteKing,
    BlackPawn,
    BlackRook,
    BlackKnight,
    BlackBishop,
    BlackQueen,
    BlackKing
};

struct Position
{
    int file;
    int rank;
};

class Piece
{
public:
    Piece(PieceTypes pieceType, const bool isWhitePiece, int file, int rank)
        : pieceType(pieceType), isWhitePiece(isWhitePiece), position{file, rank}, rank(rank), file(file)
    {}
    virtual ~Piece() = default;

    void                      move(int file, int rank);
    virtual std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) = 0;
    Position                  getPosition();
    virtual sf::Sprite&       getSprite() = 0;
    bool                      isWhite();
    PieceTypes                getType();

protected:
    PieceTypes        pieceType;
    std::vector<Move> legalMoves;
    sf::Sprite        sprite;
    bool              dragged;
    const bool        isWhitePiece;
    Position          position;
    int               rank;
    int               file;
};

class Pawn: public Piece
{
public:
    static constexpr int value = 1;

    Pawn(const bool isWhitePiece, int file, int rank, TextureLoader& textureLoader);

    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;
};

class Rook: public Piece
{
public:
    static constexpr int value = 5;

    Rook(bool isWhite, int file, int rank, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;

private:
};

class Knight: public Piece
{
public:
    static constexpr int value = 3;

    Knight(bool isWhite, int file, int rank, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;
};

class Bishop: public Piece
{
public:
    static constexpr int value = 3;

    Bishop(bool isWhite, int file, int rank, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;
};

class Queen: public Piece
{
public:
    static constexpr int value = 9;

    Queen(bool isWhite, int file, int rank, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;
};

class King: public Piece
{
public:
    static constexpr int value = INT_MAX;

    King(bool isWhite, int file, int rank, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite&       getSprite() override;
    std::vector<Move> getLegalMoves(Board& board, MoveGen& moveGen) override;

private:
};