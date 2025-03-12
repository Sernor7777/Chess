#pragma once

#include <array>
#include <cstdint>

#include "magic_bitboard.hpp"
#include "types.hpp"

class AttackGenerator
{
public:
    AttackGenerator() = delete;

    static void initialize();

    static uint64_t getRookAttacks(uint64_t occupancy, Square square)
    {
        return magicBitboard.getRookAttacks(occupancy, square);
    }
    static uint64_t getBishopAttacks(uint64_t occupancy, Square square)
    {
        return magicBitboard.getBishopAttacks(occupancy, square);
    }
    static uint64_t getQueenAttacks(uint64_t occupancy, Square square)
    {
        return getBishopAttacks(occupancy, square) | getRookAttacks(occupancy, square);
    }
    static uint64_t getKnightAttacks(Square square) { return knightTable[square]; }
    static uint64_t getKingAttacks(Square square) { return kingTable[square]; }

private:
    static const MagicBitboard             magicBitboard;
    static std::array<uint64_t, SQUARE_NB> knightTable;
    static std::array<uint64_t, SQUARE_NB> kingTable;

    static void generateKnightAttackTable();
    static void generateKingAttackTable();
};