#include <iostream>

#include "piece.hpp"
#include "board.hpp"

void Piece::move(int file, int rank)
{
    position.file = file;
    position.rank = rank;
    this->file = file;
    this->rank = rank;
}

PieceTypes Piece::getType()
{
    //std::cout << "Piece type value: " << static_cast<int>(isWhitePiece ? static_cast<PieceTypes>(0) : static_cast<PieceTypes>(6)) << std::endl;
    std::cout << pieceType << '\n';
    return pieceType;
}

Position Piece::getPosition()
{
    //std::cout << "file: " << position.file << '\n';
    return { position };
}

bool Piece::isWhite()
{
    return isWhitePiece;
}

Pawn::Pawn(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? PieceTypes::WhitePawn : PieceTypes::BlackPawn, isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wp.png" : "bp.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

sf::Sprite& Pawn::getSprite()
{
    return sprite;
}

std::vector<Move> Pawn::getLegalMoves(Board& board)
{
    legalMoves.clear();

    std::vector<Move> pawnMoves = MoveGen::generatePawnMoves(board, isWhitePiece);
    for (const Move& move : pawnMoves)
    {
        if (move.fromSquare == (8 * position.rank) + position.file)
        {
            legalMoves.push_back(move);
        }
    }

    // for (Move move : legalMoves)
    // {
    //     std::cout << move.fromSquare << ' ' << move.toSquare << '\n';
    // }

    return legalMoves;
}

Rook::Rook(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? static_cast<PieceTypes>(1) : static_cast <PieceTypes>(7), isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wr.png" : "br.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> Rook::getLegalMoves(Board& board)
{
    return legalMoves;
}

sf::Sprite& Rook::getSprite()
{
    return sprite;
}

Knight::Knight(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? static_cast<PieceTypes>(2) : static_cast <PieceTypes>(8), isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wn.png" : "bn.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> Knight::getLegalMoves(Board& board)
{
    legalMoves.clear();

    std::vector<Move> knightMoves = MoveGen::generateKnightMoves(board, isWhitePiece);
    for (const Move& move : knightMoves)
    {
        if (move.fromSquare == (8 * position.rank) + position.file)
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

sf::Sprite& Knight::getSprite()
{
    return sprite;
}

Bishop::Bishop(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? static_cast<PieceTypes>(3) : static_cast <PieceTypes>(9), isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wb.png" : "bb.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> Bishop::getLegalMoves(Board& board)
{
    return legalMoves;
}

sf::Sprite& Bishop::getSprite()
{
    return sprite;
}

Queen::Queen(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? static_cast<PieceTypes>(4) : static_cast <PieceTypes>(10), isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wq.png" : "bq.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> Queen::getLegalMoves(Board& board)
{
    return legalMoves;
}

sf::Sprite& Queen::getSprite()
{
    return sprite;
}

King::King(bool isWhitePiece, int rank, int file, TextureLoader& textureLoader) : Piece(isWhitePiece ? static_cast<PieceTypes>(5) : static_cast <PieceTypes>(11), isWhitePiece, rank, file)
{
    sprite.setTexture(textureLoader.getTexture(isWhitePiece ? "wk.png" : "bk.png"));
    sprite.setScale(6 / 15.0, 6 / 15.0);
    sprite.setPosition(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE));
}

std::vector<Move> King::getLegalMoves(Board& board)
{
    legalMoves.clear();

    std::vector<Move> kingMoves = MoveGen::generateKingMoves(board, isWhitePiece);
    for (const Move& move : kingMoves)
    {
        if (move.fromSquare == (8 * position.rank) + position.file)
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

sf::Sprite& King::getSprite()
{
    return sprite;
}
