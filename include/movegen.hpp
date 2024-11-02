#pragma once

#include <vector>

#include "move.hpp"
#include "bitboard.hpp"

class Board;

class MoveGen
{
public:
    static std::vector<Move> generatePawnMoves(Board& board, bool isWhite);

private:
    static std::vector<Move> legalMoves;
};
