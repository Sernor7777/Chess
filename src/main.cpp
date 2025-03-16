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

    // Perft::runPerftTests();

    // auto                          end      = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    Engine engine;
    // position.loadFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    // engine.setPosition(position);

    ChessGUI chessGUI(engine);

    return 0;
}