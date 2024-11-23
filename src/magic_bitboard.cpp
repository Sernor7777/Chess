#include "magic_bitboard.hpp"
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
    0x1841160051a00401ULL, 0x202000012224a02ULL,  0x284003005412542ULL,  0x2800a220c40502ULL,   0x68005050040308ULL,
    0x440802c810020230ULL, 0x240034002014417ULL,  0x45202411310208aULL,  0x1a08410602016172ULL, 0x830464044100e08ULL,
    0x411a31a010040808ULL, 0x200124000484405ULL,  0x60020c80000120aULL,  0x6a001002583420aULL,  0x10082020084c0051ULL,
    0x1325202008030692ULL, 0x2002026a00045020ULL, 0x41051c000052122cULL, 0x10200b000100803ULL,  0x720204000610032ULL,
    0x6818603041604002ULL, 0x1041040010020001ULL, 0x301081420025204ULL,  0x42024420826001ULL,   0x404304000131801ULL,
    0x1041090c00842100ULL, 0x144110020080240ULL,  0x1211004002202008ULL, 0x105080000500401ULL,  0x2080600c62080131ULL,
    0x844100114022082ULL,  0x841080020804b00ULL,  0x8240800080210ULL,    0x4002144012084210ULL, 0x2052000060904ULL,
    0x88400420500c14ULL,   0x434000204404ULL,     0x1840240800212081ULL, 0x4208c019244184ULL,   0x54da10030841ULL,
    0x1200090011080a02ULL, 0x800140c000414c8ULL,  0x4400382000401058ULL, 0x100020140000105ULL,  0x610040040044421ULL,
    0x20001202848110aULL,  0x222011010300101ULL,  0x106608008012304ULL,  0x220429002014a02ULL,  0x110800a005104208ULL,
    0x806201048200111ULL,  0x2082008a03000802ULL, 0x2041008034011420ULL, 0x401006005004434ULL,  0x90a429004080204ULL,
    0x2041040950041802ULL, 0x1002200028441145ULL, 0x109004012802018aULL, 0x65100405500801ULL,   0x284240458180a00ULL,
    0x2002441020024020ULL, 0x4a10110101144112ULL, 0x1010a2c00005030ULL,  0x40c012121020424ULL};

const std::array<int, 64> MagicBitboard::ROOK_BITS_SHIFT = {12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
                                                            11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

const std::array<int, 64> MagicBitboard::BISHOP_BITS_SHIFT = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

MagicBitboard::MagicBitboard() { generateRookAttackTable(); }

uint64_t MagicBitboard::getRookAttacks(uint64_t occupancy, int square) const
{
    uint64_t index   = generateMagicIndex(occupancy, square);
    uint64_t attacks = rookTable[square].attacks[index];

    return rookTable[square].attacks[index];
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
            uint64_t index                   = generateMagicIndex(blocker, square);
            rookTable[square].attacks[index] = calculateRookAttacks(blocker, square);
        }
    }
}

uint64_t MagicBitboard::generateMagicIndex(uint64_t occupancy, int square) const
{
    return ((occupancy & rookTable[square].mask) * rookTable[square].magic) >> rookTable[square].shift;
}
