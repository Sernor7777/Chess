#include "events.hpp"

namespace Events
{
void processEvents(sf::RenderWindow& window, ChessGUI& chessGUI)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { window.close(); }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) { window.close(); }
        }
        chessGUI.handleInput(window, event);
    }
}
}  // namespace Events