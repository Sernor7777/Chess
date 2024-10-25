#include "piece.hpp"
#include <iostream>

Pawn::Pawn(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wp.png" : "bp.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Pawn::getSprite()
{
    return sprite;
}

Rook::Rook(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wr.png" : "br.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Rook::getSprite()
{
    return sprite;
}

Knight::Knight(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wn.png" : "bn.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Knight::getSprite()
{
    return sprite;
}

Bishop::Bishop(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wb.png" : "bb.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Bishop::getSprite()
{
    return sprite;
}

Queen::Queen(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wq.png" : "bq.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Queen::getSprite()
{
    return sprite;
}

King::King(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wk.png" : "bk.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& King::getSprite()
{
    return sprite;
}
