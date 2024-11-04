#pragma once

#include <vector>

#include "move.hpp"
#include "bitboard.hpp"



class Board;

class MoveGen
{
public:
    static std::vector<Move> generatePawnMoves(Board& board, bool isWhite);
    static std::vector<Move> generateKnightMoves(Board& board, bool isWhite);
    static std::vector<Move> generateKingMoves(Board& board, bool isWhite);

    static std::vector<Move> generateHorizontalSlidingMoves(Board& board, bool isWhite);

    //static Bitboard rookAttacks(int square, Board& board);

private:
    static std::vector<Move> legalMoves;

    
};
