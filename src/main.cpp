#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "config.hpp"
#include "texture_loader.hpp"
#include "events.hpp"
#include "board.hpp"
#include "piece.hpp"

int main()
{
    TextureLoader textureLoader;

    sf::RenderWindow window(sf::VideoMode(1024, 576), "Chess");
    window.setFramerateLimit(10);

    Board board(textureLoader);
    // board.readFEN("5r2/3R4/6pk/1r5p/3P1B2/4P1P1/5P1P/1N3RK1");
    // board.readFEN("PPPPPPPP/RNBQKBNR/8/8/8/8/rnbqkbnr/pppppppp");
    // board.readFEN("8/4P3/8/1p1P4/8/8/8/8");

    // sf::Clock clock;
    // float fps;

    

    while (window.isOpen())
    {
        processEvents(window, board);
        // float deltaTime = clock.restart().asSeconds();
        // fps = 1.0f / deltaTime;

        window.clear();

        //std::cout << "awdwd" << std::endl;
        board.displayBoard(window, textureLoader);

        // window.setTitle("Chess     FPS: " + std::to_string(fps));

        window.display();
    }
}