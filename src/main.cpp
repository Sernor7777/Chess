#include <iostream>
#include <chrono>

#include "attack_generator.hpp"
#include "chess_gui.hpp"
#include "perft.hpp"
#include "position.hpp"
#include "types.hpp"


int main()
{
    AttackGenerator::initialize();

    // Position position;

    // auto start = std::chrono::high_resolution_clock::now();

    // std::vector<Move> moves;
    // std::cout << "Perft result: " << Perft::perft(position, 6, moves) << '\n';

    // Perft::runPerftTests();

    // auto                          end      = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    Engine engine;
    // position.loadFen("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    // engine.setPosition(position);

    ChessGUI chessGUI(engine);

    return 0;
}