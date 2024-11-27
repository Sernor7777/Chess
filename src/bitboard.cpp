#include <iostream>

#include "bitboard.hpp"

void Bitboard::print(uint64_t bitboard)
{
    // std::string s = "+---+---+---+---+---+---+---+---+\n";

    // for (int r = 7; r >= 0; --r)
    // {
    //     for (int f = 0; f <= 7; ++f)
    //         s += board & isOccupied((8 * r) + f) ? "| X " : "|   ";

    //     s += "| " + std::to_string(1 + r) + "\n+---+---+---+---+---+---+---+---+\n";
    // }
    // s += "  a   b   c   d   e   f   g   h\n";

    // std::cout << s << '\n';

    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int square = (rank * 8) + file;
            std::cout << (Bitboard::isSet(bitboard, square) ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
    std::cout << '\n';
    std::cout << bitboard << '\n';
}