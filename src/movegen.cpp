#include <iostream>
#include <cassert>

#include "movegen.hpp"

void MoveGen::generatePawnMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    const int DIR              = side ? -1 : 1;
    const int SINGLE_PUSH      = 8 * DIR + square;
    const int DOUBLE_PUSH      = 16 * DIR + square;
    const int CAPTURE_OFFSET_7 = 7 * DIR + square;
    const int CAPTURE_OFFSET_9 = 9 * DIR + square;

    uint64_t occupancy      = position.getPieceBitboard(ALL_PIECES);
    uint64_t enemyOccupancy = position.getPieceBitboard(ALL_PIECES, static_cast<Color>(1 - side));
    File     file           = static_cast<File>(square % 8);
    Rank     rank           = static_cast<Rank>(square / 8);

    if (rank != (side ? RANK_2 : RANK_7))
    {
        Square enPassantSquare = position.getEnPassantSquare();

        if (file != (side ? FILE_H : FILE_A) && Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_7))
        {
            moves.emplace_back(square, static_cast<Square>(CAPTURE_OFFSET_7));
        }
        else if (file != (side ? FILE_H : FILE_A) && !Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_7)
                 && CAPTURE_OFFSET_7 == enPassantSquare)
        {
            moves.emplace_back(square, static_cast<Square>(CAPTURE_OFFSET_7), Move::EN_PASSANT);
        }
        if (!Bitboard::isSet(occupancy, SINGLE_PUSH))
        {
            moves.emplace_back(square, static_cast<Square>(SINGLE_PUSH));
            if (rank == (side ? RANK_7 : RANK_2) && !Bitboard::isSet(occupancy, DOUBLE_PUSH))
            {
                moves.emplace_back(square, static_cast<Square>(DOUBLE_PUSH));
            }
        }
        if (file != (side ? FILE_A : FILE_H) && Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_9))
        {
            moves.emplace_back(square, static_cast<Square>(CAPTURE_OFFSET_9));
        }
        else if (file != (side ? FILE_A : FILE_H) && !Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_9)
                 && CAPTURE_OFFSET_9 == enPassantSquare)
        {
            moves.emplace_back(square, static_cast<Square>(CAPTURE_OFFSET_9), Move::EN_PASSANT);
        }
    }
    else
    {
        auto addPromotions = [](Square square, Square to, std::vector<Move>& moves) {
            moves.emplace_back(square, to, Move::PROMOTION, ROOK);
            moves.emplace_back(square, to, Move::PROMOTION, KNIGHT);
            moves.emplace_back(square, to, Move::PROMOTION, BISHOP);
            moves.emplace_back(square, to, Move::PROMOTION, QUEEN);
        };

        if (file != (side ? FILE_H : FILE_A) && Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_7))
        {
            addPromotions(square, static_cast<Square>(CAPTURE_OFFSET_7), moves);
        }
        if (!Bitboard::isSet(occupancy, SINGLE_PUSH)) { addPromotions(square, static_cast<Square>(SINGLE_PUSH), moves); }
        if (file != (side ? FILE_A : FILE_H) && Bitboard::isSet(enemyOccupancy, CAPTURE_OFFSET_9))
        {
            addPromotions(square, static_cast<Square>(CAPTURE_OFFSET_9), moves);
        }
    }
}

void MoveGen::generateRookMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    uint64_t occupancy = position.getPieceBitboard(ALL_PIECES);
    uint64_t attacks   = AttackGenerator::getRookAttacks(occupancy, square);

    attacks &= ~position.getPieceBitboard(ALL_PIECES, side);

    moves.reserve(moves.size() + Bitboard::countBits(attacks));

    while (attacks)
    {
        Square toSquare = static_cast<Square>(Bitboard::getLSB(attacks));
        moves.emplace_back(square, toSquare);
        attacks &= attacks - 1;
    }
}

void MoveGen::generateBishopMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    uint64_t occupancy = position.getPieceBitboard(ALL_PIECES);
    uint64_t attacks   = AttackGenerator::getBishopAttacks(occupancy, square);

    attacks &= ~position.getPieceBitboard(ALL_PIECES, side);

    moves.reserve(moves.size() + Bitboard::countBits(attacks));

    while (attacks)
    {
        Square toSquare = static_cast<Square>(Bitboard::getLSB(attacks));
        moves.emplace_back(square, toSquare);
        attacks &= attacks - 1;
    }
}

void MoveGen::generateQueenMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    uint64_t occupancy = position.getPieceBitboard(ALL_PIECES);
    uint64_t attacks   = AttackGenerator::getQueenAttacks(occupancy, square);

    attacks &= ~position.getPieceBitboard(ALL_PIECES, side);

    moves.reserve(moves.size() + Bitboard::countBits(attacks));

    while (attacks)
    {
        Square toSquare = static_cast<Square>(Bitboard::getLSB(attacks));
        moves.emplace_back(square, toSquare);
        attacks &= attacks - 1;
    }
}

void MoveGen::generateKnightMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    uint64_t attacks = AttackGenerator::getKnightAttacks(square);

    attacks &= ~position.getPieceBitboard(ALL_PIECES, side);

    moves.reserve(moves.size() + Bitboard::countBits(attacks));

    while (attacks)
    {
        Square toSquare = static_cast<Square>(Bitboard::getLSB(attacks));
        moves.emplace_back(square, toSquare);
        attacks &= attacks - 1;
    }
}

void MoveGen::generateKingMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const
{
    uint64_t attacks = AttackGenerator::getKingAttacks(square);

    attacks &= ~position.getPieceBitboard(ALL_PIECES, side);

    moves.reserve(moves.size() + Bitboard::countBits(attacks) + 2);

    while (attacks)
    {
        Square toSquare = static_cast<Square>(Bitboard::getLSB(attacks));
        moves.emplace_back(square, toSquare);
        attacks &= attacks - 1;
    }

    if (position.canCastle(side ? BLACK_OO : WHITE_OO)) { moves.emplace_back(square, side ? G8 : G1, Move::CASTLING); }
    if (position.canCastle(side ? BLACK_OOO : WHITE_OOO)) { moves.emplace_back(square, side ? C8 : C1, Move::CASTLING); }
}