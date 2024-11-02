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

    sf::RenderWindow window(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), "Chess");
    window.setFramerateLimit(50);

    Board board(textureLoader);
    //board.readFEN("5r2/3R4/6pk/1r5p/3P1B2/4P1P1/5P1P/1N3RK1");

    while (window.isOpen())
    {
        processEvents(window, board);

        window.clear();

        board.displayBoard(window, textureLoader);

        window.display();
    }
}