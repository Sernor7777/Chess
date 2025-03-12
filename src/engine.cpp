#include "engine.hpp"

#include <algorithm>

Engine::Engine() { run(); }

void Engine::run() { generateAllLegalMoves(); }

void Engine::makeMove(const Move move)
{
    StateInfo state;
    position.makeMove(move, state);
    generateAllLegalMoves();
}

void Engine::undoMove() { position.undoMove(); }

void Engine::setPosition(Position& position)
{
    this->position = position;
    generateAllLegalMoves();
}

void Engine::generateAllLegalMoves()
{
    legalMoves.clear();
    std::array<Piece, SQUARE_NB> board = position.getBoard();
    ;

    uint64_t piecesBitboard = position.getPieceBitboard(ALL_PIECES);
    while (piecesBitboard)
    {
        Square    square    = static_cast<Square>(Bitboard::getLSB(piecesBitboard));
        Piece     piece     = board[square];
        PieceType pieceType = static_cast<PieceType>(piece < 7 ? piece : (piece - 6));
        if (pieceType == NO_TYPE)
        {
            piecesBitboard &= piecesBitboard - 1;
            continue;
        }

        Color pieceColor = (piece <= WHITE_KING) ? WHITE : BLACK;
        if (pieceColor != position.getSideToMove())
        {
            piecesBitboard &= piecesBitboard - 1;
            continue;
        }

        if (pieceType == PAWN) { moveGen.generatePawnMoves(position, static_cast<Square>(square), pieceColor, legalMoves); }
        else if (pieceType == ROOK)
        {
            moveGen.generateRookMoves(position, static_cast<Square>(square), pieceColor, legalMoves);
        }
        else if (pieceType == KNIGHT)
        {
            moveGen.generateKnightMoves(position, static_cast<Square>(square), pieceColor, legalMoves);
        }
        else if (pieceType == BISHOP)
        {
            moveGen.generateBishopMoves(position, static_cast<Square>(square), pieceColor, legalMoves);
        }
        else if (pieceType == QUEEN)
        {
            moveGen.generateQueenMoves(position, static_cast<Square>(square), pieceColor, legalMoves);
        }
        else if (pieceType == KING)
        {
            moveGen.generateKingMoves(position, static_cast<Square>(square), pieceColor, legalMoves);
        }

        piecesBitboard &= piecesBitboard - 1;
    }

    legalMoves.erase(
        std::remove_if(legalMoves.begin(), legalMoves.end(), [this](const Move move) { return !position.isLegal(move); }),
        legalMoves.end());
}