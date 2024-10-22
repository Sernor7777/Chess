#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "texture_loader.hpp"

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
    int fromFile;
    int fromRank;
    int toFile;
    int toRank;
};

class Piece
{
public:
    Piece(bool isWhite, int rank, int file) : isWhite(isWhite), rank(rank), file(file) {};
    virtual ~Piece() = default;

    //*virtual*/ PieceType getType(); // = 0;
    /*virtual*/ std::vector<Move> getLegalMoves(); // = 0;
    //virtual void setSprite(TextureLoader& textureLoader) = 0;
    virtual sf::Sprite& getSprite() = 0;


protected:
    std::vector<Move> legalMoves;
    sf::Sprite sprite;
    // PieceType pieceType;
    // const int value;
    bool isWhite;
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
};

class Rook : public Piece
{
public:
    static constexpr int value = 5;

    Rook(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;

private:
};

class Knight : public Piece
{
public:
    static constexpr int value = 3;
    
    Knight(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
};

class Bishop : public Piece
{
public:
    static constexpr int value = 3;

    Bishop(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
};

class Queen : public Piece
{
public:
    static constexpr int value = 9;

    Queen(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;
};

class King : public Piece
{
public:
    static constexpr int value = INT_MAX;

    King(bool isWhite, int rank, int file, TextureLoader& textureLoader);

    //void setSprite(TextureLoader& textureLoader) override;
    sf::Sprite& getSprite() override;

private:
};