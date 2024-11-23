#include "events.hpp"

void processEvents(sf::RenderWindow& window, Board& board)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { window.close(); }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) { window.close(); }
        }
        board.handleInput(window, event);
    }
}
