#include "config.hpp"
#include "board.hpp"
#include <iostream>

Board::Board()
{
    setupBoard();
}

void Board::setupBoard()
{
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    for (const std::string& piece : pieceTypes)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(config::assetsPath + "/images/" + piece + ".png"))
        {
            std::runtime_error("Failed to load texture.");
        }
        pieceTextures[piece] = texture;
        pieceTextures[piece].setSmooth(true);
        pieceSprites[piece].setTexture(pieceTextures[piece]);
        pieceSprites[piece].setScale(sf::Vector2f(0.3f, 0.3f));
    }
}

void Board::readFEN(const std::string& FEN)
{
    int row = 0;
    int col = 0;

    for (auto& r : board) {
        r.fill(' ');
    }

    for (const char& c : FEN)
    {
        if (std::isalpha(c))
        {
            board[row][col] = c;
            col++;
        }
        else if (std::isalnum(c))
        {
            col += c - '0';
        }
        else if (c == '/')
        {
            col = 0;
            row++;
        }
        
    }
}

void Board::displayBoard(sf::RenderWindow& window)
{
    sf::RectangleShape square(sf::Vector2f(config::SQUARE_SIZE, config::SQUARE_SIZE));
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(235, 236, 208) : sf::Color(115, 149, 82));
            square.setPosition(sf::Vector2f(50 + (col * config::SQUARE_SIZE), 88 + (row * config::SQUARE_SIZE)));
            window.draw(square);

            if (board[row][col] != ' ')
            {
                pieceSprites[pieceNames[board[row][col]]].setPosition(50 + (col * config::SQUARE_SIZE), 88 + (row * config::SQUARE_SIZE));
                window.draw(pieceSprites[pieceNames[board[row][col]]]);
            }
        }
    }
}