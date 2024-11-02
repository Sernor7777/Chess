#pragma once

#include <cstdint>
#include <bitset>

class Bitboard
{
public:
    Bitboard() : board(0) {};

    void setPiece(int square);
    void removePiece(int square);
    bool isOccupied(int square);
    void print();

private:
    //std::bitset<64> board{};
    uint64_t board;
};