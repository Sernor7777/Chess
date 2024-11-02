#include <iostream>
#include <bitset>

#include "bitboard.hpp"

void Bitboard::setPiece(int square)
{
    //board.set(square);
    board |= (1ULL << square);
}

void Bitboard::removePiece(int square)
{
    //board.reset(square);
    board &= ~(1ULL << square);
}

bool Bitboard::isOccupied(int square)
{
    //return board.test(square);
    return (board & (1ULL << square)) != 0 ? true : false;
}

void Bitboard::print()
{
    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int square = (rank * 8) + file;
            std::cout << (isOccupied(square) ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
    std::cout << '\n';
}