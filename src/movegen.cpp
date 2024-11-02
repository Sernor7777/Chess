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
        int rank = (square / 8);

        if (isWhite)
        {
            if (!occupiedBitboard.isOccupied(square))
            {
                continue;
            }

            //std::cout << bitboard.isOccupied(square + 8) << '\n';
            if (rank == 1 && !occupiedBitboard.isOccupied(square + 8) && !occupiedBitboard.isOccupied(square + 16))
            {
                std::cout << "this called" << '\n';
                legalMoves.push_back(Move{ square, square + 16 });
            }
            if (rank < 6)
            {
                if (!occupiedBitboard.isOccupied(square + 8))
                {
                    legalMoves.push_back(Move{ square, square + 8 });
                }
                if (occupiedByOpponent.isOccupied(square + 7))
                {
                    legalMoves.push_back(Move{ square,square + 7 });
                }
                if (occupiedByOpponent.isOccupied(square + 9))
                {
                    legalMoves.push_back(Move{ square,square + 9 });
                }
            }
        }
    }

    return legalMoves;
}