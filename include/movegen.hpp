#pragma once

#include <vector>

#include "move.hpp"
#include "bitboard.hpp"
#include "magic_bitboard.hpp"

class Board;

class MoveGen
{
public:
    MoveGen(const MagicBitboard& magicBitboard);

    std::vector<Move> generatePawnMoves(Board& board, bool isWhite);
    std::vector<Move> generateKnightMoves(Board& board, int square, bool isWhite) const;
    std::vector<Move> generateKingMoves(Board& board, int square, bool isWhite) const;
    std::vector<Move> generateRookMoves(Board& board, int square, bool isWhite) const;
    std::vector<Move> generateBishopMoves(Board& board, int square, bool isWhite) const;
    std::vector<Move> generateQueenMoves(Board& board, int square, bool isWhite) const;

private:
    std::array<Magic, 64>    rookTable;
    std::array<Magic, 64>    bishopTable;
    std::array<uint64_t, 64> knightTable;
    std::array<uint64_t, 64> kingTable;

    const MagicBitboard& magicBitboard;

    void generateKnightAttackTable();
    void generateKingAttackTable();
};
