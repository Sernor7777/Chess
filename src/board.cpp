#include "config.hpp"
#include "board.hpp"
#include "texture_loader.hpp"
#include <iostream>
#include <memory>

Board::Board(TextureLoader& textureLoader) : textureLoader(textureLoader)
{
    setupBoard();
}

void Board::setupBoard()
{
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

void Board::readFEN(const std::string& FEN)
{
    int rank = 0;
    int file = 0;

    for (auto& row : board) {
        for (auto& piece : row) {
            piece.reset();
        }
    }

    for (const char& c : FEN)
    {
        if (std::isalpha(c))
        {
            if (std::tolower(c) == 'p')
            {
                board[rank][file] = std::make_unique<Pawn>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            else if (std::tolower(c) == 'r')
            {
                board[rank][file] = std::make_unique<Rook>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            else if (std::tolower(c) == 'n')
            {
                board[rank][file] = std::make_unique<Knight>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            else if (std::tolower(c) == 'b')
            {
                board[rank][file] = std::make_unique<Bishop>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            else if (std::tolower(c) == 'q')
            {
                board[rank][file] = std::make_unique<Queen>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            else if (std::tolower(c) == 'k')
            {
                board[rank][file] = std::make_unique<King>(std::isupper(c) ? true : false, rank, file, textureLoader);
            }
            file++;
        }
        else if (std::isalnum(c))
        {
            file += c - '0';
        }
        else
        {
            file = 0;
            rank++;
        }
    }
}

void Board::displayBoard(sf::RenderWindow& window, TextureLoader& textureLoader)
{
    sf::RectangleShape square(sf::Vector2f(config::SQUARE_SIZE, config::SQUARE_SIZE));
    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            square.setFillColor((rank + file) % 2 == 0 ? sf::Color(235, 236, 208) : sf::Color(115, 149, 82));
            square.setPosition(sf::Vector2f(50 + (file * config::SQUARE_SIZE), 48 + (rank * config::SQUARE_SIZE)));
            window.draw(square);

            std::unique_ptr<Piece>& piece = board[rank][file];
            if (piece != nullptr)
            {
                window.draw(piece->getSprite());
            }
        }
    }
}

void Board::handleInput(sf::RenderWindow& window, sf::Event& event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (auto& row : board) {
            for (auto& piece : row) {
                if (piece == nullptr)
                {
                    continue;
                }

                sf::FloatRect boundingBox = piece->getSprite().getGlobalBounds();
                if (boundingBox.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    piece->getSprite().setColor(sf::Color::Red);
                }
            }
        }
    }
}

void Board::drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite)
{
    
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape hitbox(sf::Vector2f(bounds.width, bounds.height));

    hitbox.setPosition(bounds.left, bounds.top);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);
    hitbox.setFillColor(sf::Color::Transparent);
    window.draw(hitbox);
}
