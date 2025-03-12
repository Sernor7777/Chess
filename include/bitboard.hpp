#pragma once

#include <cstdint>
#include <immintrin.h>

namespace Bitboard
{
inline void setBit(uint64_t& bitboard, int index) { bitboard |= 1ULL << index; }
inline void resetBit(uint64_t& bitboard, int index) { bitboard &= ~(1ULL << index); }
inline bool isSet(uint64_t bitboard, int index) { return (bitboard & (1ULL << index)); }
inline int  countBits(uint64_t bitboard) { return _mm_popcnt_u64(bitboard); }
inline int  getLSB(uint64_t bitboard) { return _tzcnt_u64(bitboard); }

void print(uint64_t bitboard);
}  // namespace Bitboard