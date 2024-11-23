#pragma once

#include <vector>

#include "move.hpp"
#include "bitboard.hpp"
#include "magic_bitboard.hpp"

class Board;

class MoveGen
{
public:
    MoveGen(const MagicBitboard& magicBitboard) : magicBitboard(magicBitboard) {};

    std::vector<Move> generatePawnMoves(Board& board, bool isWhite);
    std::vector<Move> generateKnightMoves(Board& board, bool isWhite);
    std::vector<Move> generateKingMoves(Board& board, bool isWhite);
    std::vector<Move> generateRookMoves(Board& board, int square, bool isWhite);

private:
    const MagicBitboard& magicBitboard;
};
