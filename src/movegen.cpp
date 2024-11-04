#include <iostream>

#include "movegen.hpp"
#include "board.hpp"

std::vector<Move> MoveGen::legalMoves;

std::vector<Move> MoveGen::generatePawnMoves(Board& board, bool isWhite)
{
    legalMoves.clear();

    Bitboard occupiedBitboard = board.getBitboards()[Occupied];
    Bitboard occupiedByOpponent = board.getBitboards()[isWhite ? OccupiedByBlack : OccupiedByWhite];
    occupiedBitboard.print();

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!occupiedBitboard.isOccupied(square))
        {
            continue;
        }

        if (isWhite)
        {
            if (rank == 1 && !occupiedBitboard.isOccupied(square + 8) && !occupiedBitboard.isOccupied(square + 16))
            {
                legalMoves.push_back(Move{ square, square + 16 });
            }
            if (rank < 6)
            {
                if (!occupiedBitboard.isOccupied(square + 8))
                {
                    legalMoves.push_back(Move{ square, square + 8 });
                }
                if (occupiedByOpponent.isOccupied(square + 7) && file != 0)
                {
                    legalMoves.push_back(Move{ square,square + 7 });
                }
                if (occupiedByOpponent.isOccupied(square + 9) && file != 7)
                {
                    legalMoves.push_back(Move{ square,square + 9 });
                }
            }
        }
        else
        {
            if (rank == 6 && !occupiedBitboard.isOccupied(square - 8) && !occupiedBitboard.isOccupied(square - 16))
            {
                legalMoves.push_back(Move{ square, square - 16 });
            }
            if (rank > 1)
            {
                if (!occupiedBitboard.isOccupied(square - 8))
                {
                    legalMoves.push_back(Move{ square, square - 8 });
                }
                if (occupiedByOpponent.isOccupied(square - 7) && file != 7)
                {
                    legalMoves.push_back(Move{ square,square - 7 });
                }
                if (occupiedByOpponent.isOccupied(square - 9) && file != 0)
                {
                    legalMoves.push_back(Move{ square,square - 9 });
                }
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateKnightMoves(Board& board, bool isWhite)
{
    legalMoves.clear();

    constexpr std::array<int, 8> knightOffsets = { -17,-15,-10,-6,6,10,15,17 };
    Bitboard occupiedBitboard = board.getBitboards()[Occupied];
    Bitboard occupiedSameColor = board.getBitboards()[isWhite ? OccupiedByWhite : OccupiedByBlack];
    occupiedBitboard.print();

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!occupiedBitboard.isOccupied(square))
        {
            continue;
        }

        for (const int offset : knightOffsets)
        {
            int targetSquare = square + offset;

            int fileDiff = std::abs((targetSquare % 8) - file);
            int rankDiff = std::abs((targetSquare / 8) - rank);

            if (targetSquare < 0 || targetSquare > 63)
            {
                continue;
            }

            if (!occupiedSameColor.isOccupied(targetSquare) && ((fileDiff == 1 && rankDiff == 2) || (fileDiff == 2 && rankDiff == 1)))
            {
                legalMoves.push_back(Move{ square, targetSquare });
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateKingMoves(Board& board, bool isWhite)
{
    legalMoves.clear();

    constexpr std::array<int, 8> kingOffsets = { -9,-8,-7,-1,1,7,8,9 };
    Bitboard occupiedBitboard = board.getBitboards()[Occupied];
    Bitboard occupiedSameColor = board.getBitboards()[isWhite ? OccupiedByWhite : OccupiedByBlack];
    occupiedBitboard.print();

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        if (!occupiedBitboard.isOccupied(square))
        {
            continue;
        }

        for (const int offset : kingOffsets)
        {
            int targetSquare = square + offset;

            int fileDiff = std::abs((targetSquare % 8) - file);
            int rankDiff = std::abs((targetSquare / 8) - rank);

            if (targetSquare < 0 || targetSquare > 63)
            {
                continue;
            }

            if (!occupiedSameColor.isOccupied(targetSquare) && (fileDiff <= 1 && rankDiff <= 1))
            {
                legalMoves.push_back(Move{ square, targetSquare });
            }
        }
    }

    return legalMoves;
}

std::vector<Move> MoveGen::generateHorizontalSlidingMoves(Board& board, bool isWhite)
{

    return legalMoves;
}
