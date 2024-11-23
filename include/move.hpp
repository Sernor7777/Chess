#pragma once

#include <cstdint>

struct Move
{
    enum MoveType
    {
        NORMAL              = 0x0000,
        KING_SIDE_CASTLE    = 0x1000,
        QUEEN_SIDE_CASTLE   = 0x2000,
        PROMOTION_Q         = 0x3000,
        PROMOTION_R         = 0x4000,
        PROMOTION_B         = 0x5000,
        PROMOTION_N         = 0x6000,
        CAPTURE             = 0x8000,
        CAPTURE_PROMOTION_Q = 0x9000,
        CAPTURE_PROMOTION_R = 0xA000,
        CAPTURE_PROMOTION_B = 0xB000,
        CAPTURE_PROMOTION_N = 0xC000
    };

    Move() : data(0) {}
    Move(int from, int to, MoveType type = NORMAL) : data(from | (to << 6) | type) {}

    inline int from() const { return data & FROM_MASK; }

    inline int to() const { return (data & TO_MASK) >> 6; }

    inline MoveType type() const { return static_cast<MoveType>(data & TYPE_MASK); }

   private:
    static constexpr uint16_t FROM_MASK = 0x003F;
    static constexpr uint16_t TO_MASK   = 0x0FC0;
    static constexpr uint16_t TYPE_MASK = 0xF000;

    uint16_t data;
};