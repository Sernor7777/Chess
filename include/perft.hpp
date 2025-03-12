#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

#include "position.hpp"
#include "movegen.hpp"

namespace Perft
{
extern MagicBitboard magicBitboardP;
extern MoveGen       moveGenP;

struct PerftTest
{
    std::string fen;
    int         depth;
    uint64_t    expected_nodes;
    std::string description;
};

uint64_t perftInternal(Position& position, int depth);
uint64_t perft(Position& position, int depth, std::vector<Move>& moves);
void     generateAllLegalMoves(Position& position, std::vector<Move>& moves);

void runPerftTests();
void dividePerft(Position& position, int depth);

extern const std::vector<PerftTest> TEST_POSITIONS;

}  // namespace Perft
