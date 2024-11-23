#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "bitboard.hpp"
#include "move.hpp"

class PRNG
{
public:
    PRNG(int s) : seed(s) {}

    uint64_t sparse_rand()
    {
        seed ^= seed >> 12;
        seed ^= seed << 25;
        seed ^= seed >> 27;
        return seed * 2685821657736338717LL;
    }

private:
    uint64_t seed;
};

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

    uint64_t getRookAttacks(uint64_t occupancy, int square) const;
    uint64_t getBishopAttacks(int square, uint64_t occupancy) const;
    uint64_t getQueenAttacks(int square, uint64_t occupancy) const;

private:
    static const std::array<uint64_t, 64> ROOK_MAGIC_NUMBERS;
    static const std::array<uint64_t, 64> BISHOP_MAGIC_NUMBERS;
    static const std::array<int, 64>      ROOK_BITS_SHIFT;
    static const std::array<int, 64>      BISHOP_BITS_SHIFT;

    std::array<Magic, 64> rookTable;

    void     generateRookAttackTable();
    uint64_t calculateRookAttacks(uint64_t blockers, int square) const;
    uint64_t calculateRookMask(int square) const;

    uint64_t generateMagicIndex(uint64_t occupancy, int square) const;

    std::vector<uint64_t> generateBlockerBitboards(uint64_t mask) const;

    //void findMagicNumbers();
};