#include "attack_generator.hpp"

#include <cassert>

#include "magic_bitboard.hpp"
#include "types.hpp"

const MagicBitboard             AttackGenerator::magicBitboard;
std::array<uint64_t, SQUARE_NB> AttackGenerator::knightTable;
std::array<uint64_t, SQUARE_NB> AttackGenerator::kingTable;

void AttackGenerator::initialize()
{
    generateKnightAttackTable();
    generateKingAttackTable();
}

void AttackGenerator::generateKnightAttackTable()
{
    constexpr std::array<int, 8> knightOffsets{-17, -15, -10, -6, 6, 10, 15, 17};

    for (int square = 0; square < SQUARE_NB; ++square)
    {
        uint64_t attacks = 0;

        for (const int offset : knightOffsets)
        {
            int targetSquare = square + offset;

            if (targetSquare < A1 || targetSquare > H8) { continue; }
            if (std::abs((targetSquare % 8) - (square % 8)) <= 2) { Bitboard::setBit(attacks, targetSquare); }
        }

        knightTable[square] = attacks;
    }
}

void AttackGenerator::generateKingAttackTable()
{
    constexpr std::array<int, 8> kingOffsets{-9, -8, -7, -1, 1, 7, 8, 9};

    for (int square = 0; square < SQUARE_NB; ++square)
    {
        uint64_t attacks = 0;
        for (const int offset : kingOffsets)
        {
            int targetSquare = square + offset;
            if (targetSquare < A1 || targetSquare > H8) { continue; }
            if (std::abs((targetSquare % 8) - (square % 8)) <= 1) { Bitboard::setBit(attacks, targetSquare); }
        }
        kingTable[square] = attacks;
    }
}
