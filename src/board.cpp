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

SquareStatus Board::getSquareStatus(int rank, int file, bool isWhite)
{
    Piece* piece = board[rank][file].get();
    if (piece == nullptr)
    {
        return SquareStatus::Empty;
    }
    else if (piece->getColor() == isWhite)
    {
        return SquareStatus::Friendly;
    }
    else
    {
        return SquareStatus::Enemy;
    }
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
            square.setPosition(sf::Vector2f(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE)));
            window.draw(square);

            std::unique_ptr<Piece>& piece = board[rank][file];
            if (piece == nullptr)
            {
                continue;
            }
            if (draggedPiece != piece.get())
            {
                piece->getSprite().setPosition(square.getPosition());
                window.draw(piece->getSprite());
            }
            // drawHitbox(window, piece->getSprite());
        }
    }
    if (draggedPiece != nullptr)
    {
        window.draw(draggedPiece->getSprite());
    }
}

void Board::handleInput(sf::RenderWindow& window, sf::Event& event) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        for (auto& row : board) {
            for (auto& piece : row) {
                if (piece == nullptr) {
                    continue;
                }

                sf::FloatRect boundingBox = piece->getSprite().getGlobalBounds();
                if (boundingBox.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && draggedPiece == nullptr) {
                    piece->setDragged(true);
                    draggedPiece = piece.get();

                    // Get legal moves and check if there are any
                    auto legalMoves = draggedPiece->getLegalMoves(*this);
                    if (!legalMoves.empty()) {
                        std::cout << legalMoves[0].toRank << '\n'; // Safe access
                    }
                }

                // Check if a piece is being dragged before updating its position
                if (draggedPiece != nullptr) {
                    draggedPiece->getSprite().setPosition(
                        static_cast<sf::Vector2f>(mousePosition) -
                        sf::Vector2f(draggedPiece->getSprite().getGlobalBounds().width / 2,
                            draggedPiece->getSprite().getGlobalBounds().height / 2)
                    );
                }
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (draggedPiece != nullptr) {
            draggedPiece->setDragged(false);
            draggedPiece = nullptr;
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
