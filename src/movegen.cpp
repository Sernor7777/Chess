#include <iostream>

#include "board.hpp"
#include "movegen.hpp"

std::vector<Move> MoveGen::generatePawnMoves(Board& board, bool isWhite)
{
    std::vector<Move> legalMoves;
    uint64_t          occupiedBitboard   = board.getBitboards()[Occupied];
    uint64_t          occupiedByOpponent = board.getBitboards()[isWhite ? OccupiedByBlack : OccupiedByWhite];
    Bitboard::print(occupiedBitboard);

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!Bitboard::isSet(occupiedBitboard, square)) { continue; }

        if (isWhite)
        {
            if (rank == 1 && !Bitboard::isSet(occupiedBitboard, square + 8)
                && !Bitboard::isSet(occupiedBitboard, square + 16))
            {
                legalMoves.push_back(Move{square, square + 16});
            }
            if (rank < 6)
            {
                if (!Bitboard::isSet(occupiedBitboard, square + 8)) { legalMoves.push_back(Move{square, square + 8}); }
                if (Bitboard::isSet(occupiedByOpponent, square + 7) && file != 0)
                {
                    legalMoves.push_back(Move{square, square + 7});
                }
                if (Bitboard::isSet(occupiedByOpponent, square + 9) && file != 7)
                {
                    legalMoves.push_back(Move{square, square + 9});
                }
            }
        }
        else
        {
            if (rank == 6 && !Bitboard::isSet(occupiedBitboard, square - 8)
                && !Bitboard::isSet(occupiedBitboard, square - 16))
            {
                legalMoves.push_back(Move{square, square - 16});
            }
            if (rank > 1)
            {
                if (!Bitboard::isSet(occupiedBitboard, square - 8)) { legalMoves.push_back(Move{square, square - 8}); }
                if (Bitboard::isSet(occupiedByOpponent, square - 7) && file != 7)
                {
                    legalMoves.push_back(Move{square, square - 7});
                }
                if (Bitboard::isSet(occupiedByOpponent, square - 9) && file != 0)
                {
                    legalMoves.push_back(Move{square, square - 9});
                }
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateKnightMoves(Board& board, bool isWhite)
{
    std::vector<Move>            legalMoves;
    constexpr std::array<int, 8> knightOffsets = {-17, -15, -10, -6, 6, 10, 15, 17};

    uint64_t occupiedBitboard  = board.getBitboards()[Occupied];
    uint64_t occupiedSameColor = board.getBitboards()[isWhite ? OccupiedByWhite : OccupiedByBlack];
    Bitboard::print(occupiedBitboard);

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!Bitboard::isSet(occupiedBitboard, square)) { continue; }

        for (const int offset : knightOffsets)
        {
            int targetSquare = square + offset;

            int fileDiff = std::abs((targetSquare % 8) - file);
            int rankDiff = std::abs((targetSquare / 8) - rank);

            if (targetSquare < 0 || targetSquare > 63) { continue; }

            if (!Bitboard::isSet(occupiedSameColor, targetSquare)
                && ((fileDiff == 1 && rankDiff == 2) || (fileDiff == 2 && rankDiff == 1)))
            {
                legalMoves.push_back(Move{square, targetSquare});
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateKingMoves(Board& board, bool isWhite)
{
    std::vector<Move>            legalMoves;
    constexpr std::array<int, 8> kingOffsets = {-9, -8, -7, -1, 1, 7, 8, 9};

    uint64_t occupiedBitboard  = board.getBitboards()[Occupied];
    uint64_t occupiedSameColor = board.getBitboards()[isWhite ? OccupiedByWhite : OccupiedByBlack];
    Bitboard::print(occupiedBitboard);

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!Bitboard::isSet(occupiedBitboard, square)) { continue; }

        for (const int offset : kingOffsets)
        {
            int targetSquare = square + offset;

            int fileDiff = std::abs((targetSquare % 8) - file);
            int rankDiff = std::abs((targetSquare / 8) - rank);

            if (targetSquare < 0 || targetSquare > 63) { continue; }

            if (!Bitboard::isSet(occupiedSameColor, targetSquare) && (fileDiff <= 1 && rankDiff <= 1))
            {
                legalMoves.push_back(Move{square, targetSquare});
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateRookMoves(Board& board, int square, bool isWhite)
{
    std::vector<Move> legalMoves;
    uint64_t          occupancy = board.getBitboards()[Occupied];
    uint64_t          attacks   = magicBitboard.getRookAttacks(occupancy, square);

    attacks &= ~board.getBitboards()[isWhite ? OccupiedByWhite : OccupiedByBlack];

    legalMoves.reserve(Bitboard::countBits(attacks));

    while (attacks)
    {
        int            toSquare  = Bitboard::getLSB(attacks);
        bool           isCapture = (occupancy & (1ULL << toSquare)) != 0;
        Move::MoveType type      = isCapture ? Move::CAPTURE : Move::NORMAL;
        legalMoves.emplace_back(Move{square, toSquare, type});
        attacks &= attacks - 1;
    }

    return legalMoves;
}
