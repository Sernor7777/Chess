#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "config.hpp"
#include "texture_loader.hpp"
#include "events.hpp"
#include "magic_bitboard.hpp"
#include "sound_manager.hpp"
#include "attack_generator.hpp"
#include "chess_gui.hpp"
#include "perft.hpp"
#include "position.hpp"

#include <thread>
#include <chrono>
#include <cassert>
#include <filesystem>

int main()
{
    AttackGenerator::initialize();

    // auto start = std::chrono::high_resolution_clock::now();

    // std::vector<Move> moves;
    // std::cout << "Perft result: " << Perft::perft(position, 6, moves) << '\n';

    // Perft::runPerftTests();

    // auto                          end      = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    Position position;

    Engine engine;
    // position.loadFen("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    // engine.setPosition(position);

    ChessGUI chessGUI(engine);

    return 0;
}