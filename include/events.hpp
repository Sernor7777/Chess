#pragma once

#include <SFML/Window.hpp>

#include "chess_gui.hpp"

namespace Events
{
void processEvents(sf::RenderWindow& window, ChessGUI& chessGUI);  //, Board& board);
}  // namespace events
