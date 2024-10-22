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

    // sf::Texture texture;
    // for (const std::string& piece : pieceTypes)
    // {
    //     if (!texture.loadFromFile(config::assetsPath + "/images/" + piece + ".png"))
    //     {
    //         std::runtime_error("Failed to load texture!");
    //     }
    //     pieceTextures[piece] = texture;
    //     pieceTextures[piece].setSmooth(true);
    //     pieceSprites[piece].setTexture(pieceTextures[piece]);
    //     pieceSprites[piece].setScale(1 / 3.f, 1 / 3.f);
    //     //sf::Vector2f scale = pieceSprites[piece].getScale();
    //     //std::cout << "Scale: x = " << scale.x << ", y = " << scale.y << std::endl;


    // }
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
                //pieceSprites[pieceNames[board[rank][file]]].setPosition(50 + (file * config::SQUARE_SIZE), 88 + (rank * config::SQUARE_SIZE));
                //window.draw(pieceSprites[pieceNames[board[rank][file]]]);
                // drawHitbox(window, pieceSprites[pieceNames[board[rank][file]]]);
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
                if (piece != nullptr)
                {
                    sf::FloatRect boundingBox = piece->getSprite().getGlobalBounds();
                    if (boundingBox.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        piece->getSprite().setColor(sf::Color::Red);
                        std::cout << "oh wow this is called" << '\n';
                    }
                }
            }
        }
    }
}

void Board::drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite)
{
    // Get the bounding box of the sprite
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // Create a rectangle shape to represent the hitbox
    sf::RectangleShape hitbox(sf::Vector2f(bounds.width, bounds.height));

    // Set the position of the hitbox to match the sprite's position
    hitbox.setPosition(bounds.left, bounds.top);

    // Set a visible outline for the hitbox
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);

    // Make the inside of the hitbox transparent
    hitbox.setFillColor(sf::Color::Transparent);

    // Draw the hitbox to the window
    window.draw(hitbox);
}
