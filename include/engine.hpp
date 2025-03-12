#pragma once

#include <vector>

#include "position.hpp"
#include "movegen.hpp"
#include "types.hpp"

class Engine
{
public:
    Engine();

    void run();

    void makeMove(const Move move);
    void undoMove();

    void            setPosition(Position& position);
    const Position& getPosition() const { return position; }

    std::vector<Move> getLegalMoves() const { return legalMoves; }

private:
    Position          position;
    MoveGen           moveGen;
    std::vector<Move> legalMoves;

    void generateAllLegalMoves();
};