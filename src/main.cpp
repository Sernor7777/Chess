#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "config.hpp"
#include "events.hpp"
#include "board.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Chess");
    window.setFramerateLimit(144);

    Board board;
    // board.readFEN("5r2/3R4/6pk/1r5p/3P1B2/4P1P1/5P1P/1N3RK1");

    // sf::Clock clock;
    // float fps;

    while (window.isOpen())
    {
        processEvents(window);

        // float deltaTime = clock.restart().asSeconds();
        // fps = 1.0f / deltaTime;

        window.clear();

        board.displayBoard(window);

        // window.setTitle("Chess     FPS: " + std::to_string(fps));

        window.display();
    }
}