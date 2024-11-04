#pragma once

#include <cstdint>
#include <array>
#include <vector>

#include "move.hpp"
#include "bitboard.hpp"

struct Magic {
    uint64_t* ptr;
    Bitboard mask;
    uint64_t magic;
    int shift;
};

class MagicBitboard
{
public:
    MagicBitboard();

    std::array<uint64_t, 64>& getRookMagicNumbers();
    std::array<uint64_t, 64>& getBishopMagicNumbers();
    
private:
    //Magic rookTable[64];
    std::array<uint64_t, 64> rookMagicNumbers;
    std::array<uint64_t, 64> bishopMagicNumbers;

    std::array<Bitboard, 64> rookMasks;

    std::array<Magic, 64> rookTable;

    std::vector<uint64_t> rookAttackTable;


    std::array<int, 64> rookBitsShift;
    std::array<int, 64> bishopBitsShift;

    std::vector<Bitboard>& generateRookAttackTable();
    std::array<Bitboard, 64>& generateRookMasks();

};