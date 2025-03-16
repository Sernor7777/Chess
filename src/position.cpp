#include "position.hpp"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "bitboard.hpp"
#include "attack_generator.hpp"

Position::Position() { loadFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0"); }

void Position::loadFen(const std::string& fen)
{
    moveHistory.clear();
    stateHistory.clear();
    stateHistory.emplace_back();  // I don't like this

    std::istringstream fenStream(fen);
    std::string        boardSubStr, turnSubStr, castlingSubStr, enPassantSubStr, plySubStr;

    fenStream >> boardSubStr >> turnSubStr >> castlingSubStr >> enPassantSubStr;  // >> plySubStr;

    piecesBitboards.fill(0ULL);
    colorBitboards.fill(0ULL);
    board.fill(NO_PIECE);

    int       square = A8;
    PieceType pieceType;
    for (const char c : boardSubStr)
    {
        if (std::isdigit(c)) { square += c - '0'; }
        else if (c == '/') { square -= 16; }
        else
        {
            if (std::tolower(c) == 'p') { pieceType = PAWN; }
            else if (std::tolower(c) == 'r') { pieceType = ROOK; }
            else if (std::tolower(c) == 'n') { pieceType = KNIGHT; }
            else if (std::tolower(c) == 'b') { pieceType = BISHOP; }
            else if (std::tolower(c) == 'q') { pieceType = QUEEN; }
            else if (std::tolower(c) == 'k') { pieceType = KING; }

            Bitboard::setBit(piecesBitboards[pieceType], square);
            Bitboard::setBit(colorBitboards[std::isupper(c) ? WHITE : BLACK], square);
            board[square] = static_cast<Piece>(pieceType + (std::isupper(c) ? 0 : 6));

            ++square;
        }
    }
    piecesBitboards[ALL_PIECES] = colorBitboards[WHITE] | colorBitboards[BLACK];

    sideToMove = turnSubStr == "w" ? WHITE : BLACK;

    for (const char c : castlingSubStr)
    {
        if (c == '-') { break; }
        else if (c == 'K') { stateHistory.back().castlingRights |= WHITE_OO; }
        else if (c == 'Q') { stateHistory.back().castlingRights |= WHITE_OOO; }
        else if (c == 'k') { stateHistory.back().castlingRights |= BLACK_OO; }
        else if (c == 'q') { stateHistory.back().castlingRights |= BLACK_OOO; }
    }

    if (enPassantSubStr != "-")
    {
        stateHistory.back().enPassantSquare =
            static_cast<Square>((enPassantSubStr[1] - '1') * 8 + (enPassantSubStr[0] - 'a'));
    }

    // ply = std::stoi(plySubStr);
}

bool Position::canCastle(CastlingRights castlingRight) const
{
    if (!(castlingRight & stateHistory.back().castlingRights) || Bitboard::countBits(castlingRight) != 1) { return false; }

    if (castlingRight == WHITE_OO)
    {
        return !(Bitboard::isSet(piecesBitboards[ALL_PIECES], F1) || Bitboard::isSet(piecesBitboards[ALL_PIECES], G1));
    }
    else if (castlingRight == WHITE_OOO)
    {
        return !(Bitboard::isSet(piecesBitboards[ALL_PIECES], B1) || Bitboard::isSet(piecesBitboards[ALL_PIECES], C1)
                 || Bitboard::isSet(piecesBitboards[ALL_PIECES], D1));
    }
    else if (castlingRight == BLACK_OO)
    {
        return !(Bitboard::isSet(piecesBitboards[ALL_PIECES], F8) || Bitboard::isSet(piecesBitboards[ALL_PIECES], G8));
    }
    else
    {
        return !(Bitboard::isSet(piecesBitboards[ALL_PIECES], B8) || Bitboard::isSet(piecesBitboards[ALL_PIECES], C8)
                 || Bitboard::isSet(piecesBitboards[ALL_PIECES], D8));
    }
}

bool Position::isLegal(Move move, StateInfo& newState)
{
    if (move.type() == Move::CASTLING)
    {
        if (isSquareAttacked(static_cast<Square>(Bitboard::getLSB(piecesBitboards[KING] & colorBitboards[sideToMove])),
                             static_cast<Color>(1 - sideToMove)))
        {
            return false;
        }

        Square from = move.from();
        Square to   = move.to();

        int    direction   = (to > from) ? 1 : -1;
        Square passThrough = static_cast<Square>(from + direction);

        if (isSquareAttacked(passThrough, static_cast<Color>(1 - sideToMove))) { return false; }

        if (isSquareAttacked(to, static_cast<Color>(1 - sideToMove))) { return false; }
        return true;
    }

    if (board[move.from()] == (sideToMove ? WHITE_KING : BLACK_KING))
    {
        return !isSquareAttacked(static_cast<Square>(move.to()), static_cast<Color>(1 - sideToMove));
    }

    makeMove(move, newState);

    bool isLegal =
        !isSquareAttacked(static_cast<Square>(Bitboard::getLSB(piecesBitboards[KING] & colorBitboards[1 - sideToMove])),
                          static_cast<Color>(sideToMove));

    undoMove();
    return isLegal;
}

void Position::filterLegalMoves(std::vector<Move>& moves)
{
    StateInfo newState;

    moves.erase(std::remove_if(moves.begin(), moves.end(),
                               [this, &newState](const Move move) {
                                   newState = {};
                                   return !isLegal(move, newState);
                               }),
                moves.end());
}

void Position::makeMove(Move move, StateInfo& newState)
{
    newState.castlingRights = stateHistory.back().castlingRights;
    newState.rule50         = ++stateHistory.back().rule50;

    Piece     boardPiece = board[move.from()];
    PieceType pieceType  = static_cast<PieceType>(boardPiece - 6 * sideToMove);

    Piece     capturedPiece     = NO_PIECE;
    PieceType capturedPieceType = NO_TYPE;
    Square    capturedPieceIndex;
    if (board[move.to()] != NO_PIECE)
    {
        capturedPiece      = board[move.to()];
        capturedPieceType  = static_cast<PieceType>(capturedPiece - 6 * (1 - sideToMove));
        capturedPieceIndex = move.to();
    }

    if (move.type() == Move::CASTLING)
    {
        Square rookFrom, rookTo;
        if (move.to() == G1)
        {
            rookFrom = H1;
            rookTo   = F1;
        }
        else if (move.to() == C1)
        {
            rookFrom = A1;
            rookTo   = D1;
        }
        else if (move.to() == G8)
        {
            rookFrom = H8;
            rookTo   = F8;
        }
        else
        {
            rookFrom = A8;
            rookTo   = D8;
        }

        movePiece(rookFrom, rookTo, sideToMove);
        movePiece(move.from(), move.to(), sideToMove);

        newState.castlingRights &= static_cast<CastlingRights>(sideToMove ? WHITE_OO | WHITE_OOO : BLACK_OO | BLACK_OOO);
    }
    else if (move.type() == Move::EN_PASSANT)
    {
        movePiece(move.from(), move.to(), sideToMove);
        removePiece(static_cast<Square>(move.to() + 8 * (sideToMove ? 1 : -1)));
        newState.capturedPiece = static_cast<Piece>(PAWN + 6 * sideToMove);
    }
    else if (move.type() == Move::PROMOTION)
    {
        if (capturedPiece)
        {
            removePiece(move.to());
            newState.capturedPiece = capturedPiece;
        }

        removePiece(move.from());
        placePiece(static_cast<Piece>(move.promotionPiece() + 6 * sideToMove), move.to());
    }
    else
    {
        if (capturedPiece)
        {
            removePiece(move.to());
            newState.capturedPiece = capturedPiece;
            newState.rule50        = 0;

            if (capturedPieceType == ROOK)
            {
                if (capturedPieceIndex == H1) { newState.castlingRights &= static_cast<CastlingRights>(~WHITE_OO); }
                else if (capturedPieceIndex == A1) { newState.castlingRights &= static_cast<CastlingRights>(~WHITE_OOO); }
                else if (capturedPieceIndex == H8) { newState.castlingRights &= static_cast<CastlingRights>(~BLACK_OO); }
                else if (capturedPieceIndex == A8) { newState.castlingRights &= static_cast<CastlingRights>(~BLACK_OOO); }
            }
        }

        movePiece(move.from(), move.to(), sideToMove);

        if (pieceType == PAWN)
        {
            newState.rule50 = 0;

            if (std::abs(move.to() - move.from()) == 16)
            {
                newState.enPassantSquare = static_cast<Square>(move.from() + 8 * (sideToMove ? -1 : 1));
            }
        }
        else if (pieceType == ROOK)
        {
            if (move.from() == H1) { newState.castlingRights &= static_cast<CastlingRights>(~WHITE_OO); }
            else if (move.from() == A1) { newState.castlingRights &= static_cast<CastlingRights>(~WHITE_OOO); }
            else if (move.from() == H8) { newState.castlingRights &= static_cast<CastlingRights>(~BLACK_OO); }
            else if (move.from() == A8) { newState.castlingRights &= static_cast<CastlingRights>(~BLACK_OOO); }
        }
        else if (pieceType == KING)
        {
            newState.castlingRights &= static_cast<CastlingRights>(sideToMove ? WHITE_OO | WHITE_OOO : BLACK_OO | BLACK_OOO);
        }
    }

    // if (newState.rule50 == 100) { Some code to end the game with a Draw; }
    sideToMove = static_cast<Color>(1 - sideToMove);

    stateHistory.push_back(newState);
    moveHistory.push_back(move);
}

void Position::undoMove()
{
    Move move = moveHistory.back();

    sideToMove = static_cast<Color>(1 - sideToMove);

    if (move.type() == Move::CASTLING)
    {
        Square rookFrom, rookTo;
        if (move.to() == G1)
        {
            rookFrom = F1;
            rookTo   = H1;
        }
        else if (move.to() == C1)
        {
            rookFrom = D1;
            rookTo   = A1;
        }
        else if (move.to() == G8)
        {
            rookFrom = F8;
            rookTo   = H8;
        }
        else
        {
            rookFrom = D8;
            rookTo   = A8;
        }

        movePiece(move.to(), move.from(), sideToMove);
        movePiece(rookFrom, rookTo, sideToMove);
    }
    else if (move.type() == Move::EN_PASSANT)
    {
        movePiece(move.to(), move.from(), sideToMove);
        Square capturedPawnSquare = static_cast<Square>(move.to() + 8 * (sideToMove ? 1 : -1));
        placePiece(static_cast<Piece>(PAWN + 6 * (1 - sideToMove)), capturedPawnSquare);
    }
    else if (move.type() == Move::PROMOTION)
    {
        removePiece(move.to());
        placePiece(static_cast<Piece>(PAWN + 6 * sideToMove), move.from());

        if (stateHistory.back().capturedPiece != NO_PIECE) { placePiece(stateHistory.back().capturedPiece, move.to()); }
    }
    else
    {
        movePiece(move.to(), move.from(), sideToMove);
        if (stateHistory.back().capturedPiece != NO_PIECE) { placePiece(stateHistory.back().capturedPiece, move.to()); }
    }

    stateHistory.pop_back();
    moveHistory.pop_back();
}

bool Position::isSquareAttacked(Square square, Color opponent) const
{
    const int DIR = opponent ? 1 : -1;

    uint64_t opponentBitboard = colorBitboards[opponent];
    uint64_t queenBitboard    = piecesBitboards[QUEEN];

    uint64_t pawnBitboard = piecesBitboards[PAWN] & opponentBitboard;
    File     file         = static_cast<File>(square % 8);
    if (file != (opponent ? FILE_A : FILE_H))
    {
        if (Bitboard::isSet(pawnBitboard, square + (7 * DIR))) { return true; }
    }
    if (file != (opponent ? FILE_H : FILE_A))
    {
        if (Bitboard::isSet(pawnBitboard, square + (9 * DIR))) { return true; }
    }

    uint64_t rookAttackMask = AttackGenerator::getRookAttacks(piecesBitboards[ALL_PIECES], square);
    if (rookAttackMask & ((piecesBitboards[ROOK] | queenBitboard) & opponentBitboard)) { return true; }

    uint64_t bishopAttackMask = AttackGenerator::getBishopAttacks(piecesBitboards[ALL_PIECES], square);
    if (bishopAttackMask & ((piecesBitboards[BISHOP] | queenBitboard) & opponentBitboard)) { return true; }

    uint64_t knightAttacks = AttackGenerator::getKnightAttacks(square);
    if (knightAttacks & (piecesBitboards[KNIGHT] & colorBitboards[opponent])) { return true; }

    uint64_t kingAttacks = AttackGenerator::getKingAttacks(square);
    if (kingAttacks & (piecesBitboards[KING] & colorBitboards[opponent])) { return true; }

    return false;
}

void Position::printFen()
{
    std::string fen;

    for (int rank = RANK_8; rank >= RANK_1; --rank)
    {
        int emptySquares = 0;

        for (int file = FILE_A; file <= FILE_H; ++file)
        {
            Square square = static_cast<Square>(8 * rank + file);
            Piece  piece  = board[square];

            if (piece == NO_PIECE) { ++emptySquares; }
            else
            {
                if (emptySquares > 0)
                {
                    fen += std::to_string(emptySquares);
                    emptySquares = 0;
                }

                char pieceChar;
                if (piece == WHITE_PAWN) { pieceChar = 'P'; }
                else if (piece == WHITE_ROOK) { pieceChar = 'R'; }
                else if (piece == WHITE_KNIGHT) { pieceChar = 'N'; }
                else if (piece == WHITE_BISHOP) { pieceChar = 'B'; }
                else if (piece == WHITE_QUEEN) { pieceChar = 'Q'; }
                else if (piece == WHITE_KING) { pieceChar = 'K'; }
                else if (piece == BLACK_PAWN) { pieceChar = 'p'; }
                else if (piece == BLACK_ROOK) { pieceChar = 'r'; }
                else if (piece == BLACK_KNIGHT) { pieceChar = 'n'; }
                else if (piece == BLACK_BISHOP) { pieceChar = 'b'; }
                else if (piece == BLACK_QUEEN) { pieceChar = 'q'; }
                else if (piece == BLACK_KING) { pieceChar = 'k'; }

                fen += pieceChar;
            }
        }
        if (emptySquares > 0) { fen += std::to_string(emptySquares); }
        if (rank > RANK_1) { fen += '/'; }
    }

    fen += ' ';
    fen += sideToMove == WHITE ? 'w' : 'b';

    fen += ' ';
    if (stateHistory.back().castlingRights == NO_CASTLING_RIGHTS) { fen += '-'; }
    else
    {
        if (stateHistory.back().castlingRights & WHITE_OO) fen += 'K';
        if (stateHistory.back().castlingRights & WHITE_OOO) fen += 'Q';
        if (stateHistory.back().castlingRights & BLACK_OO) fen += 'k';
        if (stateHistory.back().castlingRights & BLACK_OOO) fen += 'q';
    }

    fen += ' ';
    if (stateHistory.back().enPassantSquare == SQ_NONE) { fen += '-'; }
    else
    {
        char file = 'a' + (stateHistory.back().enPassantSquare % 8);
        char rank = '1' + (stateHistory.back().enPassantSquare / 8);
        fen += file;
        fen += rank;
    }

    fen += ' ';
    fen += std::to_string(stateHistory.back().rule50);

    fen += ' ';
    fen += std::to_string(moveHistory.size() / 2 + 1);

    std::cout << fen << std::endl;
}