#include "piece.hpp"
#include "board.hpp"
#include <iostream>

bool Piece::getColor()
{
    return isWhite;
}

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

std::vector<Move> Pawn::getLegalMoves(Board& board) {
    std::cout << "getLegalMoves called for Pawn at rank: " << rank << " file: " << file << std::endl;
    if (rank == 6 && isWhite)
    {
        legalMoves.push_back(Move{ rank, file, rank - 1, file });
    }
    return legalMoves;
}

Rook::Rook(bool isWhite, int rank, int file, TextureLoader& textureLoader) : Piece(isWhite, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhite ? "wr.png" : "br.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> Rook::getLegalMoves(Board& board)
{
    if (rank == 2 && isWhite && board.getSquareStatus(rank + 1, file, isWhite) == 0)
    {
        legalMoves.push_back(Move{ rank, file, rank + 1, file });
    }
    return legalMoves;
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

std::vector<Move> Knight::getLegalMoves(Board& board)
{
    if (rank == 2 && isWhite && board.getSquareStatus(rank + 1, file, isWhite) == 0)
    {
        legalMoves.push_back(Move{ rank, file, rank + 1, file });
    }
    return legalMoves;
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

std::vector<Move> Bishop::getLegalMoves(Board& board)
{
    if (rank == 2 && isWhite && board.getSquareStatus(rank + 1, file, isWhite) == 0)
    {
        legalMoves.push_back(Move{ rank, file, rank + 1, file });
    }
    return legalMoves;
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

std::vector<Move> Queen::getLegalMoves(Board& board)
{
    if (rank == 2 && isWhite && board.getSquareStatus(rank + 1, file, isWhite) == 0)
    {
        legalMoves.push_back(Move{ rank, file, rank + 1, file });
    }
    return legalMoves;
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

std::vector<Move> King::getLegalMoves(Board& board)
{
    if (rank == 2 && isWhite && board.getSquareStatus(rank + 1, file, isWhite) == 0)
    {
        legalMoves.push_back(Move{ rank, file, rank + 1, file });
    }
    return legalMoves;
}

sf::Sprite& King::getSprite()
{
    return sprite;
}
