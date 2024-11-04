#include "config.hpp"
#include "board.hpp"
#include "texture_loader.hpp"
#include <iostream>
#include <memory>

Board::Board(TextureLoader& textureLoader, MagicBitboard& magicBitboard) : textureLoader(textureLoader), magicBitboard(magicBitboard)
{
    setupBoard();
}

void Board::setupBoard()
{
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

//void Board::makeMove(int fromFile, int fromRank, int toFile, int toRank, PieceTypes pieceType)
void Board::makeMove(Move move, PieceTypes pieceType)
{
    int fromSquare = move.fromSquare;
    int toSquare = move.toSquare;

    if (bitboards[Occupied].isOccupied(toSquare))
    {
        board[toSquare].reset();
        bitboards[board[fromSquare]->isWhite() ? OccupiedByBlack : OccupiedByWhite].removePiece(toSquare);
    }

    board[fromSquare]->move(toSquare % 8, toSquare / 8);
    board[toSquare] = std::move(board[fromSquare]);

    bitboards[Occupied].removePiece(fromSquare);
    bitboards[Occupied].setPiece(toSquare);
    bitboards[pieceType].removePiece(fromSquare);
    bitboards[pieceType].setPiece(toSquare);
    if (pieceType <= 5)
    {
        bitboards[OccupiedByWhite].removePiece(fromSquare);
        bitboards[OccupiedByWhite].setPiece(toSquare);
    }
    else
    {
        bitboards[OccupiedByBlack].removePiece(fromSquare);
        bitboards[OccupiedByBlack].setPiece(toSquare);
    }

    legalMoves.clear();
}

void Board::readFEN(const std::string& FEN)
{
    int square = 0;
    int file = 0;
    int rank = 7;

    std::fill(board.begin(), board.end(), nullptr);
    bitboards.fill(Bitboard());

    for (const char& c : FEN)
    {
        if (std::isalpha(c))
        {
            square = (8 * (rank)) + file;
            if (std::tolower(c) == 'p')
            {
                board[square] = std::make_unique<Pawn>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhitePawn : PieceTypes::BlackPawn].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
            }
            else if (std::tolower(c) == 'r')
            {
                board[square] = std::make_unique<Rook>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhiteRook : PieceTypes::BlackRook].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
            }
            else if (std::tolower(c) == 'n')
            {
                board[square] = std::make_unique<Knight>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhiteKnight : PieceTypes::BlackKnight].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
            }
            else if (std::tolower(c) == 'b')
            {
                board[square] = std::make_unique<Bishop>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhiteBishop : PieceTypes::BlackBishop].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
            }
            else if (std::tolower(c) == 'q')
            {
                board[square] = std::make_unique<Queen>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhiteQueen : PieceTypes::BlackQueen].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
            }
            else if (std::tolower(c) == 'k')
            {
                board[square] = std::make_unique<King>(std::isupper(c) ? true : false, file, rank, textureLoader);
                bitboards[std::isupper(c) ? PieceTypes::WhiteKing : PieceTypes::BlackKing].setPiece(square);
                bitboards[Occupied].setPiece(square);
                bitboards[std::isupper(c) ? OccupiedByWhite : OccupiedByBlack].setPiece(square);
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
        for (const Move& move : legalMoves)
        {
            if ((8 * (7 - rank)) + file == move.toSquare)
            {
                square.setFillColor((file + rank) % 2 == 0 ? sf::Color(235, 125, 106) : sf::Color(211, 108, 80));
            }
        }

        square.setPosition(sf::Vector2f(50 + (file * config::SQUARE_SIZE), (config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2 + (rank * config::SQUARE_SIZE)));
        window.draw(square);

        std::unique_ptr<Piece>& piece = board[i];
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
    if (draggedPiece != nullptr)
    {
        window.draw(draggedPiece->getSprite());
    }
}

void Board::handleInput(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (auto& piece : board)
        {
            if (piece == nullptr)
            {
                continue;
            }

            sf::FloatRect boundingBox = piece->getSprite().getGlobalBounds();
            if (boundingBox.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && draggedPiece == nullptr)
            {
                draggedPiece = piece.get();
                legalMoves = draggedPiece->getLegalMoves(*this);
            }

            if (draggedPiece != nullptr)
            {
                draggedPiece->getSprite().setPosition(static_cast<sf::Vector2f>(mousePosition) - sf::Vector2f(draggedPiece->getSprite().getGlobalBounds().width / 2, draggedPiece->getSprite().getGlobalBounds().height / 2));
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (draggedPiece == nullptr)
        {
            return;
        }

        int targetRank = ((mousePosition.y - ((config::WINDOW_HEIGHT - (8 * config::SQUARE_SIZE)) / 2)) / config::SQUARE_SIZE);
        targetRank = 7 - targetRank;
        int targetFile = (mousePosition.x - 50) / config::SQUARE_SIZE;
        //legalMoves = draggedPiece->getLegalMoves(*this);
        for (const Move& move : legalMoves)
        {
            if (move.toSquare == (8 * (targetRank)) + targetFile)
            {
                //makeMove(draggedPiece->getPosition().file, draggedPiece->getPosition().rank, targetFile, targetRank, draggedPiece->getType());
                makeMove(move, draggedPiece->getType());
            }
        }

        legalMoves.clear();
        draggedPiece = nullptr;
    }
}

std::array<Bitboard, 17>& Board::getBitboards()
{
    return bitboards;
}

std::array<uint64_t, 64>& Board::getRookMagicNumbers()
{
    return magicBitboard.getRookMagicNumbers();
}

std::array<uint64_t, 64>& Board::getBishopMagicNumbers()
{
    return magicBitboard.getBishopMagicNumbers();
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
