#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "bitboard.hpp"

struct Magic
{
    uint64_t* attacks;
    uint64_t  mask;
    uint64_t  magic;
    int       shift;
};

class MagicBitboard
{
public:
    MagicBitboard();

    uint64_t getRookAttacks(uint64_t occupancy, int square) const
    {
        return rookTable[square].attacks[generateRookMagicIndex(occupancy, square)];
    }
    uint64_t getBishopAttacks(uint64_t occupancy, int square) const
    {
        return bishopTable[square].attacks[generateBishopMagicIndex(occupancy, square)];
    }
    uint64_t getQueenAttacks(uint64_t occupancy, int square) const
    {
        return getBishopAttacks(occupancy, square) | getRookAttacks(occupancy, square);
    }

private:
    static const std::array<uint64_t, 64> ROOK_MAGIC_NUMBERS;
    static const std::array<uint64_t, 64> BISHOP_MAGIC_NUMBERS;
    static const std::array<int, 64>      ROOK_BITS_SHIFT;
    static const std::array<int, 64>      BISHOP_BITS_SHIFT;

    std::array<Magic, 64> rookTable;
    std::array<Magic, 64> bishopTable;

    void generateRookAttackTable();
    void generateBishopAttackTable();

    uint64_t calculateRookAttacks(uint64_t blockers, int square) const;
    uint64_t calculateBishopAttacks(uint64_t blockers, int square) const;
    uint64_t calculateRookMask(int square) const;
    uint64_t calculateBishopMask(int square) const;

    std::vector<uint64_t> generateBlockerBitboards(uint64_t mask) const;

    uint64_t generateRookMagicIndex(uint64_t occupancy, int square) const
    {
        return ((occupancy & rookTable[square].mask) * rookTable[square].magic) >> rookTable[square].shift;
    }
    uint64_t generateBishopMagicIndex(uint64_t occupancy, int square) const
    {
        return ((occupancy & bishopTable[square].mask) * bishopTable[square].magic) >> bishopTable[square].shift;
    }
};