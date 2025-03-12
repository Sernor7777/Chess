#pragma once

#include <vector>

#include "attack_generator.hpp"
#include "bitboard.hpp"
#include "magic_bitboard.hpp"
#include "position.hpp"

struct MoveGen
{
    MoveGen() = default;

    void generatePawnMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
    void generateKnightMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
    void generateKingMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
    void generateRookMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
    void generateBishopMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
    void generateQueenMoves(const Position& position, Square square, Color side, std::vector<Move>& moves) const;
};
