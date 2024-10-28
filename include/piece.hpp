#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "texture_loader.hpp"
// #include "board.hpp"

class Board;

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

struct Move
{
    int fromRank;
    int fromFile;
    int toRank;
    int toFile;
};

class Piece
{
public:
    Piece(bool isWhite, int rank, int file) : isWhite(isWhite), rank(rank), file(file) {};
    virtual ~Piece() = default;

    //*virtual*/ PieceType getType(); // = 0;
    virtual std::vector<Move> getLegalMoves(Board& board) = 0;
    //virtual void setSprite(TextureLoader& textureLoader) = 0;
    virtual sf::Sprite& getSprite() = 0;
    bool getColor();
    void setDragged(bool dragged);
    bool isDragged();


protected:
    std::vector<Move> legalMoves;
    sf::Sprite sprite;
    // PieceType pieceType;
    // const int value;
    bool isWhite;
    bool dragged;
    int rank;
    int file;
};

class Pawn : public Piece
{
public:
    static constexpr int value = 1;
    
    Pawn(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;
};

class Rook : public Piece
{
public:
    static constexpr int value = 5;

    Rook(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;

private:
};

class Knight : public Piece
{
public:
    static constexpr int value = 3;
    
    Knight(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;
};

class Bishop : public Piece
{
public:
    static constexpr int value = 3;

    Bishop(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;
};

class Queen : public Piece
{
public:
    static constexpr int value = 9;

    Queen(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;
};

class King : public Piece
{
public:
    static constexpr int value = INT_MAX;

    King(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
    std::vector<Move> getLegalMoves(Board& board) override;

private:
};