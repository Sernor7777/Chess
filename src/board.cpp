#include "board.hpp"
#include "config.hpp"
#include "texture_loader.hpp"
#include <iostream>
#include <memory>

Board::Board(TextureLoader& textureLoader) : textureLoader(textureLoader), magicBitboard(), moveGen(magicBitboard)
{
    setupBoard();
}

void Board::setupBoard()
{
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    getLegalMoves();
}

void Board::makeMove(Move move, PieceTypes pieceType)
{
    int fromSquare = move.from();
    int toSquare   = move.to();

    if (Bitboard::isSet(bitboards[Occupied], toSquare))
    {
        board[toSquare].reset();
        Bitboard::resetBit(bitboards[board[fromSquare]->isWhite() ? OccupiedByBlack : OccupiedByWhite], toSquare);
    }

    board[fromSquare]->move(toSquare % 8, toSquare / 8);
    board[toSquare] = std::move(board[fromSquare]);

    Bitboard::resetBit(bitboards[Occupied], fromSquare);
    Bitboard::setBit(bitboards[Occupied], toSquare);
    Bitboard::resetBit(bitboards[pieceType], fromSquare);
    Bitboard::setBit(bitboards[pieceType], toSquare);

    if (pieceType <= 5)
    {
        Bitboard::resetBit(bitboards[OccupiedByWhite], fromSquare);
        Bitboard::setBit(bitboards[OccupiedByWhite], toSquare);
    }
    else
    {
        Bitboard::resetBit(bitboards[OccupiedByBlack], fromSquare);
        Bitboard::setBit(bitboards[OccupiedByBlack], toSquare);
    }

    getLegalMoves();
}

void Board::readFEN(const std::string& FEN)
{
    int square = 0;
    int file   = 0;
    int rank   = 7;

    std::fill(board.begin(), board.end(), nullptr);
    bitboards.fill(0ULL);

    for (const char& c : FEN)
    {
        if (std::isalpha(c))
        {
            square = (8 * (rank)) + file;
            if (std::tolower(c) == 'p')
            {
                board[square] = std::make_unique<Pawn>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhitePawn : PieceTypes::BlackPawn], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            else if (std::tolower(c) == 'r')
            {
                board[square] = std::make_unique<Rook>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhiteRook : PieceTypes::BlackRook], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            else if (std::tolower(c) == 'n')
            {
                board[square] = std::make_unique<Knight>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhiteKnight : PieceTypes::BlackKnight], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            else if (std::tolower(c) == 'b')
            {
                board[square] = std::make_unique<Bishop>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhiteBishop : PieceTypes::BlackBishop], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            else if (std::tolower(c) == 'q')
            {
                board[square] = std::make_unique<Queen>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhiteQueen : PieceTypes::BlackQueen], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            else if (std::tolower(c) == 'k')
            {
                board[square] = std::make_unique<King>(std::isupper(c) ? true : false, file, rank, textureLoader);
                Bitboard::setBit(bitboards[std::isupper(c) ? PieceTypes::WhiteKing : PieceTypes::BlackKing], square);
                Bitboard::setBit(bitboards[Occupied], square);
                Bitboard::setBit(bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack], square);
            }
            file++;
        }
        else if (std::isalnum(c)) { file += c - '0'; }
        else
        {
            file = 0;
            rank--;
        }
    }
}

void Board::displayBoard(sf::RenderWindow& window, TextureLoader& textureLoader)
{
    sf::RectangleShape square(sf::Vector2f(config::SQUARE_SIZE, config::SQUARE_SIZE));
    for (int i = 0; i < 64; i++)
    {
        int file = i % 8;
        int rank = 7 - (i / 8);
        square.setFillColor((file + rank) % 2 == 0 ? sf::Color(235, 236, 208) : sf::Color(115, 149, 82));
        if (draggedPiece)
        {
            for (const Move& move : legalMoves)
            {
                if ((8 * (7 - rank)) + file == move.to()
                    && draggedPiece->getPosition().rank * 8 + draggedPiece->getPosition().file == move.from())
                {
                    square.setFillColor((file + rank) % 2 == 0 ? sf::Color(235, 125, 106) : sf::Color(211, 108, 80));
                }
            }
        }

        square.setPosition(
            sf::Vector2f(50 + (file * config::SQUARE_SIZE),
                         (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE)));
        window.draw(square);

        std::unique_ptr<Piece>& piece = board[i];
        if (piece == nullptr) { continue; }
        if (draggedPiece != piece.get())
        {
            piece->getSprite().setPosition(square.getPosition());
            window.draw(piece->getSprite());
        }
        // drawHitbox(window, piece->getSprite());
    }
    if (draggedPiece != nullptr) { window.draw(draggedPiece->getSprite()); }
}

void Board::handleInput(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (const auto& piece : board)
        {
            if (piece == nullptr) { continue; }

            sf::FloatRect boundingBox = piece->getSprite().getGlobalBounds();
            if (boundingBox.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))
                && draggedPiece == nullptr)
            {
                draggedPiece = piece.get();
            }

            if (draggedPiece != nullptr)
            {
                draggedPiece->getSprite().setPosition(
                    static_cast<sf::Vector2f>(mousePosition)
                    - sf::Vector2f(draggedPiece->getSprite().getGlobalBounds().width / 2,
                                   draggedPiece->getSprite().getGlobalBounds().height / 2));
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (draggedPiece == nullptr) { return; }

        int targetRank =
            ((mousePosition.y - ((config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2)) / config::SQUARE_SIZE);
        targetRank     = 7 - targetRank;
        int targetFile = (mousePosition.x - 50) / config::SQUARE_SIZE;
        for (const Move& move : legalMoves)
        {
            if (move.to() == (8 * (targetRank)) + targetFile
                && draggedPiece->getPosition().rank * 8 + draggedPiece->getPosition().file == move.from())
            {
                makeMove(move, draggedPiece->getType());
            }
        }

        draggedPiece = nullptr;
    }
}

std::array<uint64_t, 17>& Board::getBitboards() { return bitboards; }

void Board::drawHitbox(sf::RenderWindow& window, const sf::Sprite& sprite)
{
    sf::FloatRect      bounds = sprite.getGlobalBounds();
    sf::RectangleShape hitbox(sf::Vector2f(bounds.width, bounds.height));

    hitbox.setPosition(bounds.left, bounds.top);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);
    hitbox.setFillColor(sf::Color::Transparent);
    window.draw(hitbox);
}

void Board::getLegalMoves()
{
    legalMoves.clear();

    for (const auto& piece : board)
    {
        if (piece)
        {
            std::vector<Move> moves = piece->getLegalMoves(*this, moveGen);
            legalMoves.insert(legalMoves.end(), moves.begin(), moves.end());
        }
    }
}
