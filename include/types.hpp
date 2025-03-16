#pragma once

#include <cstdint>
#include <string>

enum PieceType
{
    NO_TYPE,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    ALL_PIECES    = 0,
    PIECE_TYPE_NB = 7
};

enum Piece
{
    NO_PIECE,
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_QUEEN,
    WHITE_KING,
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_QUEEN,
    BLACK_KING,
    PIECE_NB
};

enum Color
{
    WHITE,
    BLACK,
    COLOR_NB
};

enum Square
{
    // clang-format off

    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    SQ_NONE,
    SQUARE_NB = 64,
    // clang-format on
};

enum File
{
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB
};

enum Rank
{
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB
};

class Move
{
public:
    enum MoveType
    {
        NORMAL,
        CASTLING   = 0x1000,
        PROMOTION  = 0x2000,
        EN_PASSANT = 0x3000
    };

    Move() = default;
    Move(Square from, Square to, MoveType type = NORMAL, PieceType promotionType = static_cast<PieceType>(2))
        : data(from | (to << 6) | type | (promotionType - 2) << 14)
    {}

    constexpr Square    from() const { return static_cast<Square>(data & FROM_MASK); }
    constexpr Square    to() const { return static_cast<Square>((data & TO_MASK) >> 6); }
    constexpr MoveType  type() const { return static_cast<MoveType>(data & (3 << 12)); }
    constexpr PieceType promotionPiece() const
    {
        PieceType pieceType = static_cast<PieceType>((data >> 14) + 2);
        return (type() == PROMOTION) ? static_cast<PieceType>((data >> 14) + 2) : NO_TYPE;
    }

    std::string toString() const
    {
        static const char* const SQUARE_NAMES[64] = {
            "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
            "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
            "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
            "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"};

        static const char* const PROMOTION_PIECES = "rnbq";

        std::string moveStr;

        if (type() == CASTLING) { return (to() > from() ? "O-O" : "O-O-O"); }

        moveStr = SQUARE_NAMES[from()];
        moveStr += SQUARE_NAMES[to()];

        if (type() == PROMOTION) { moveStr += PROMOTION_PIECES[promotionPiece() - 2]; }

        return moveStr;
    }

private:
    static constexpr uint16_t FROM_MASK = 0x003F;
    static constexpr uint16_t TO_MASK   = 0x0FC0;

    uint16_t data = 0;
};