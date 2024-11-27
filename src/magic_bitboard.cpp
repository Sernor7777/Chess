#include "magic_bitboard.hpp"
#include <unordered_map>
#include <iostream>

const std::array<uint64_t, 64> MagicBitboard::ROOK_MAGIC_NUMBERS = {
    0x80004000208011ULL,   0x2100102100804000ULL, 0x80200080100008ULL,   0x680061000800800ULL,  0x200100200082004ULL,
    0x2200010402001008ULL, 0x80020000800100ULL,   0x100002100038052ULL,  0x802040008000ULL,     0x11002100804000ULL,
    0x1210802000801008ULL, 0x101000c20100101ULL,  0x40808008000400ULL,   0x2202800400800200ULL, 0x91003200110004ULL,
    0x490800040800100ULL,  0x508000c000200048ULL, 0x4e0004000300041ULL,  0x30008010802000ULL,   0x1010008010800800ULL,
    0x401c808008000400ULL, 0x984008080040200ULL,  0x2000400c1121008ULL,  0x20020024488104ULL,   0x4940802080004002ULL,
    0xc0100140200042ULL,   0x2124100200101ULL,    0x8900084200201201ULL, 0x8050100100800ULL,    0x24000480800200ULL,
    0x81014002e0841ULL,    0x400008200012844ULL,  0x4080002000400040ULL, 0x80400080200aULL,     0x10008010802000ULL,
    0x48041000800881ULL,   0x41101000800ULL,      0x2000280800400ULL,    0x202482104001012ULL,  0x440082000041ULL,
    0x180400080008020ULL,  0x9120005000204002ULL, 0x8088420082160020ULL, 0x810100008008080ULL,  0x1020800850010ULL,
    0x6000400410680120ULL, 0x90583002040081ULL,   0x10000100a0420004ULL, 0x8800804200210200ULL, 0x1000400880200480ULL,
    0x4602028040201a00ULL, 0x1008801000480180ULL, 0x40080080080ULL,      0x40040002008080ULL,   0x20a20108104400ULL,
    0x104650c008200ULL,    0x2300800020190041ULL, 0x4a481014001d7ULL,    0x8024204208120082ULL, 0x29000905201001ULL,
    0x4003000230480005ULL, 0xc101000208040001ULL, 0x8421001080084ULL,    0x1120502084010052ULL};

const std::array<uint64_t, 64> MagicBitboard::BISHOP_MAGIC_NUMBERS = {
    0x40106000A1160020ULL, 0x20010250810120ULL,   0x2010010220280081ULL, 0x2806004050C040ULL,   0x2021018000000ULL,
    0x2001112010000400ULL, 0x881010120218080ULL,  0x1030820110010500ULL, 0x120222042400ULL,     0x2000020404040044ULL,
    0x8000480094208000ULL, 0x3422A02000001ULL,    0xA220210100040ULL,    0x8004820202226000ULL, 0x18234854100800ULL,
    0x100004042101040ULL,  0x4001004082820ULL,    0x10000810010048ULL,   0x1014004208081300ULL, 0x2080818802044202ULL,
    0x40880C00A00100ULL,   0x80400200522010ULL,   0x1000188180B04ULL,    0x80249202020204ULL,   0x1004400004100410ULL,
    0x13100A0022206ULL,    0x2148500001040080ULL, 0x4241080011004300ULL, 0x4020848004002000ULL, 0x10101380D1004100ULL,
    0x8004422020284ULL,    0x1010A1041008080ULL,  0x808080400082121ULL,  0x808080400082121ULL,  0x91128200100C00ULL,
    0x202200802010104ULL,  0x8C0A020200440085ULL, 0x1A0008080B10040ULL,  0x889520080122800ULL,  0x100902022202010AULL,
    0x4081A0816002000ULL,  0x681208005000ULL,     0x8170840041008802ULL, 0xA00004200810805ULL,  0x830404408210100ULL,
    0x2602208106006102ULL, 0x1048300680802628ULL, 0x2602208106006102ULL, 0x602010120110040ULL,  0x941010801043000ULL,
    0x40440A210428ULL,     0x8240020880021ULL,    0x400002012048200ULL,  0xAC102001210220ULL,   0x220021002009900ULL,
    0x84440C080A013080ULL, 0x1008044200440ULL,    0x4C04410841000ULL,    0x2000500104011130ULL, 0x1A0C010011C20229ULL,
    0x44800112202200ULL,   0x434804908100424ULL,  0x300404822C08200ULL,  0x48081010008A2A80ULL};

const std::array<int, 64> MagicBitboard::ROOK_BITS_SHIFT = {12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

const std::array<int, 64> MagicBitboard::BISHOP_BITS_SHIFT = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

MagicBitboard::MagicBitboard()
{
    generateRookAttackTable();
    generateBishopAttackTable();
}

uint64_t MagicBitboard::getRookAttacks(uint64_t occupancy, int square) const
{
    uint64_t index = generateRookMagicIndex(occupancy, square);

    return rookTable[square].attacks[index];
}

uint64_t MagicBitboard::getBishopAttacks(uint64_t occupancy, int square) const
{
    uint64_t index = generateBishopMagicIndex(occupancy, square);

    return bishopTable[square].attacks[index];
}

uint64_t MagicBitboard::getQueenAttacks(uint64_t occupancy, int square) const
{
    uint64_t rookIndex   = generateRookMagicIndex(occupancy, square);
    uint64_t bishopIndex = generateBishopMagicIndex(occupancy, square);

    return bishopTable[square].attacks[bishopIndex] | rookTable[square].attacks[rookIndex];
}

uint64_t MagicBitboard::calculateRookMask(int square) const
{
    uint64_t mask = 0ULL;
    int      file = square % 8;
    int      rank = square / 8;

    for (int f = file + 1; f < 7; ++f)
    {
        Bitboard::setBit(mask, (rank * 8) + f);
    }

    for (int f = file - 1; f > 0; --f)
    {
        Bitboard::setBit(mask, (rank * 8) + f);
    }

    for (int r = rank + 1; r < 7; ++r)
    {
        Bitboard::setBit(mask, (r * 8) + file);
    }

    for (int r = rank - 1; r > 0; --r)
    {
        Bitboard::setBit(mask, (r * 8) + file);
    }

    return mask;
}

uint64_t MagicBitboard::calculateRookAttacks(uint64_t blockers, int square) const
{
    uint64_t attacks = 0ULL;
    int      file    = square % 8;
    int      rank    = square / 8;

    for (int f = file + 1; f <= 7; ++f)
    {
        int sq = (rank * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int f = file - 1; f >= 0; --f)
    {
        int sq = (rank * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int r = rank + 1; r <= 7; ++r)
    {
        int sq = (r * 8) + file;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int r = rank - 1; r >= 0; --r)
    {
        int sq = (r * 8) + file;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    return attacks;
}

std::vector<uint64_t> MagicBitboard::generateBlockerBitboards(uint64_t mask) const
{
    std::vector<uint64_t> blockers;
    uint64_t              subset = 0ULL;

    blockers.reserve(1ULL << Bitboard::countBits(mask));

    do
    {
        blockers.push_back(subset);
        subset = (subset - mask) & mask;
    } while (subset);

    return blockers;
}

void MagicBitboard::generateRookAttackTable()
{
    for (int square = 0; square < 64; ++square)
    {
        uint64_t mask = calculateRookMask(square);

        rookTable[square].mask    = mask;
        rookTable[square].magic   = ROOK_MAGIC_NUMBERS[square];
        rookTable[square].shift   = 64 - ROOK_BITS_SHIFT[square];
        rookTable[square].attacks = new uint64_t[1 << Bitboard::countBits(mask)];

        std::vector<uint64_t> blockers = generateBlockerBitboards(mask);

        for (uint64_t blocker : blockers)
        {
            uint64_t index                   = generateRookMagicIndex(blocker, square);
            rookTable[square].attacks[index] = calculateRookAttacks(blocker, square);
        }
    }
}

void MagicBitboard::generateBishopAttackTable()
{
    for (int square = 0; square < 64; ++square)
    {
        uint64_t mask = calculateBishopMask(square);

        bishopTable[square].mask    = mask;
        bishopTable[square].magic   = BISHOP_MAGIC_NUMBERS[square];
        bishopTable[square].shift   = 64 - BISHOP_BITS_SHIFT[square];
        bishopTable[square].attacks = new uint64_t[1 << Bitboard::countBits(mask)];

        std::vector<uint64_t> blockers = generateBlockerBitboards(mask);

        for (uint64_t blocker : blockers)
        {
            uint64_t index                     = generateBishopMagicIndex(blocker, square);
            bishopTable[square].attacks[index] = calculateBishopAttacks(blocker, square);
        }
    }
}

uint64_t MagicBitboard::generateRookMagicIndex(uint64_t occupancy, int square) const
{
    return ((occupancy & rookTable[square].mask) * rookTable[square].magic) >> rookTable[square].shift;
}

uint64_t MagicBitboard::generateBishopMagicIndex(uint64_t occupancy, int square) const
{
    return ((occupancy & bishopTable[square].mask) * bishopTable[square].magic) >> bishopTable[square].shift;
}

uint64_t MagicBitboard::calculateBishopAttacks(uint64_t blockers, int square) const
{
    uint64_t attacks = 0ULL;
    int      file    = square % 8;
    int      rank    = square / 8;

    for (int f = file + 1, r = rank + 1; f <= 7 && r <= 7; ++f, ++r)
    {
        int sq = (r * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int f = file + 1, r = rank - 1; f <= 7 && r >= 0; ++f, --r)
    {
        int sq = (r * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int f = file - 1, r = rank + 1; f >= 0 && r <= 7; --f, ++r)
    {
        int sq = (r * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    for (int f = file - 1, r = rank - 1; f >= 0 && r >= 0; --f, --r)
    {
        int sq = (r * 8) + f;
        Bitboard::setBit(attacks, sq);
        if ((1ULL << sq) & blockers) { break; }
    }

    return attacks;
}

uint64_t MagicBitboard::calculateBishopMask(int square) const
{
    uint64_t mask = 0ULL;
    int      file = square % 8;
    int      rank = square / 8;

    for (int f = file + 1, r = rank + 1; f < 7 && r < 7; ++f, ++r)
    {
        Bitboard::setBit(mask, (r * 8) + f);
    }

    for (int f = file + 1, r = rank - 1; f < 7 && r > 0; ++f, --r)
    {
        Bitboard::setBit(mask, (r * 8) + f);
    }

    for (int f = file - 1, r = rank + 1; f > 0 && r < 7; --f, ++r)
    {
        Bitboard::setBit(mask, (r * 8) + f);
    }

    for (int f = file - 1, r = rank - 1; f > 0 && r > 0; --f, --r)
    {
        Bitboard::setBit(mask, (r * 8) + f);
    }

    return mask;
}
