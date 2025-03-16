#include "chess_gui.hpp"

#include <array>
#include <iostream>
#include <cassert>

#include "events.hpp"
#include "config.hpp"

ChessGUI::ChessGUI(Engine& engine) : engine(engine) { run(); }

void ChessGUI::run()
{
    window.create(sf::VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT), "Chess");
    window.setFramerateLimit(60);

    sprite.setScale(config::SQUARE_SIZE / 150, config::SQUARE_SIZE / 150);
    legalMoves = engine.getLegalMoves();

    soundManager.playSound("game-start.mp3");

    while (window.isOpen())
    {
        Events::processEvents(window, *this);
        soundManager.update();
        window.clear();
        drawBoard(window);
        window.display();
    }
}

void ChessGUI::drawBoard(sf::RenderWindow& window)
{
    sf::RectangleShape square(sf::Vector2f(config::SQUARE_SIZE, config::SQUARE_SIZE));

    File file = static_cast<File>(draggedPieceIndex % 8);
    Rank rank = static_cast<Rank>(draggedPieceIndex / 8);

    for (int sq = A1; sq < SQUARE_NB; ++sq)
    {
        file = static_cast<File>(sq % 8);
        rank = static_cast<Rank>(sq / 8);
        square.setFillColor((file + rank) % 2 == 0 ? sf::Color(115, 149, 82) : sf::Color(235, 236, 208));

        square.setPosition(
            sf::Vector2f(file * config::SQUARE_SIZE + 50,
                         (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + ((7 - rank) * config::SQUARE_SIZE)));
        window.draw(square);
    }

    if (draggedPieceIndex != SQ_NONE)
    {
        for (const Move move : legalMoves)
        {
            if (draggedPieceIndex == move.from())
            {
                square.setFillColor((move.to() % 8 + move.to() / 8) % 2 == 0 ? sf::Color(211, 108, 80)
                                                                             : sf::Color(235, 125, 106));
                square.setPosition(sf::Vector2f(move.to() % 8 * config::SQUARE_SIZE + 50,
                                                (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2
                                                    + ((7 - move.to() / 8) * config::SQUARE_SIZE)));
                window.draw(square);
            }
        }
    }

    for (int sq = A1; sq < SQUARE_NB; ++sq)
    {
        Piece piece = engine.getPosition().getBoard()[sq];
        if (!piece) { continue; }

        file = static_cast<File>(sq % 8);
        rank = static_cast<Rank>(sq / 8);

        if (draggedPieceIndex != sq)
        {
            setPieceSprite(piece);
            sprite.setPosition(
                sf::Vector2f(file * config::SQUARE_SIZE + 50,
                             (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + ((7 - rank) * config::SQUARE_SIZE)));
            window.draw(sprite);
        }
    }

    if (draggedPieceIndex != SQ_NONE)
    {
        Piece draggedPiece = engine.getPosition().getBoard()[draggedPieceIndex];
        setPieceSprite(draggedPiece);
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))
                           - sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2));
        window.draw(sprite);
    }
}

void ChessGUI::handleInput(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    File         file          = static_cast<File>((mousePosition.x - 50) / config::SQUARE_SIZE);
    Rank         rank =
        static_cast<Rank>(7
                          - static_cast<int>((mousePosition.y - ((config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2))
                                             / static_cast<float>(config::SQUARE_SIZE)));

    if (mousePosition.x < 50 || mousePosition.x >= 50 + 8 * config::SQUARE_SIZE
        || mousePosition.y < (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2
        || mousePosition.y >= (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + 8 * config::SQUARE_SIZE)
    {
        return;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (file < FILE_A || file > FILE_H || rank < RANK_1 || rank > RANK_8) { return; }
        if (draggedPieceIndex != SQ_NONE || engine.getPosition().getBoard()[8 * rank + file] == NO_PIECE) { return; }
        draggedPieceIndex = static_cast<Square>((8 * rank) + file);
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (draggedPieceIndex == SQ_NONE) { return; }

        for (const Move move : legalMoves)
        {
            if (move.to() == 8 * rank + file && draggedPieceIndex == move.from())
            {
                engine.makeMove(move);
                legalMoves = engine.getLegalMoves();
                break;
            }
        }

        draggedPieceIndex = SQ_NONE;
    }
}

void ChessGUI::setPieceSprite(Piece piece)
{
    {
        if (piece == WHITE_PAWN)
            sprite.setTexture(textureLoader.getTexture("wp.png"));
        else if (piece == WHITE_ROOK)
            sprite.setTexture(textureLoader.getTexture("wr.png"));
        else if (piece == WHITE_KNIGHT)
            sprite.setTexture(textureLoader.getTexture("wn.png"));
        else if (piece == WHITE_BISHOP)
            sprite.setTexture(textureLoader.getTexture("wb.png"));
        else if (piece == WHITE_QUEEN)
            sprite.setTexture(textureLoader.getTexture("wq.png"));
        else if (piece == WHITE_KING)
            sprite.setTexture(textureLoader.getTexture("wk.png"));
        else if (piece == BLACK_PAWN)
            sprite.setTexture(textureLoader.getTexture("bp.png"));
        else if (piece == BLACK_ROOK)
            sprite.setTexture(textureLoader.getTexture("br.png"));
        else if (piece == BLACK_KNIGHT)
            sprite.setTexture(textureLoader.getTexture("bn.png"));
        else if (piece == BLACK_BISHOP)
            sprite.setTexture(textureLoader.getTexture("bb.png"));
        else if (piece == BLACK_QUEEN)
            sprite.setTexture(textureLoader.getTexture("bq.png"));
        else if (piece == BLACK_KING)
            sprite.setTexture(textureLoader.getTexture("bk.png"));
    }
}