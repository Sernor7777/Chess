#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <forward_list>
#include <deque>
#include <vector>

#include "bitboard.hpp"
#include "types.hpp"

enum CastlingRights
{
    NO_CASTLING_RIGHTS,
    WHITE_OO  = 1,
    WHITE_OOO = 2,
    BLACK_OO  = 4,
    BLACK_OOO = 8
};

inline CastlingRights operator|(CastlingRights a, CastlingRights b)
{
    return static_cast<CastlingRights>(static_cast<int>(a) | static_cast<int>(b));
}
inline CastlingRights operator&(CastlingRights a, CastlingRights b)
{
    return static_cast<CastlingRights>(static_cast<int>(a) & static_cast<int>(b));
}
inline CastlingRights& operator|=(CastlingRights& a, CastlingRights b) { return a = a | b; }
inline CastlingRights& operator&=(CastlingRights& a, CastlingRights b) { return a = a & b; }

struct StateInfo
{
    CastlingRights castlingRights  = NO_CASTLING_RIGHTS;
    int            rule50          = 0;
    Square         enPassantSquare = SQ_NONE;
    Piece          capturedPiece   = NO_PIECE;
};

class Position
{
public:
    Position();

    void loadFen(const std::string& fen);

    void makeMove(Move move, StateInfo& newState);
    void undoMove();

    bool isLegal(Move move);
    void filterLegalMoves(std::vector<Move>& moves);

    bool canCastle(CastlingRights castlingRight) const;

    uint64_t getPieceBitboard(int type) const { return piecesBitboards[type]; }
    uint64_t getPieceBitboard(PieceType type, Color color) const { return piecesBitboards[type] & colorBitboards[color]; }

    Square                       getEnPassantSquare() const { return stateHistory.back().enPassantSquare; }
    std::array<Piece, SQUARE_NB> getBoard() const { return board; }
    Color                        getSideToMove() const { return sideToMove; }
    // bool isRepeatedPosition() const; Will add Zobrist hashing in the future

    void printFen();

private:
    std::array<uint64_t, PIECE_TYPE_NB> piecesBitboards;
    std::array<uint64_t, COLOR_NB>      colorBitboards;
    std::array<Piece, SQUARE_NB>        board;

    std::deque<StateInfo> stateHistory;
    std::deque<Move>      moveHistory;

    Color sideToMove;
    // int ply = 0; Could use this in the future to count moves

    bool isSquareAttacked(Square square, Color opponent) const;

    void movePiece(Square from, Square to, Color color);

    void placePiece(Piece piece, Square square);
    void removePiece(Square square);
};

inline void Position::movePiece(Square from, Square to, Color color)
{
    piecesBitboards[ALL_PIECES] ^= (1ULL << from) | (1ULL << to);
    piecesBitboards[board[from] - (6 * (color ? 1 : 0))] ^= (1ULL << from) | (1ULL << to);
    colorBitboards[color] ^= (1ULL << from) | (1ULL << to);
    board[to]   = board[from];
    board[from] = NO_PIECE;
}

inline void Position::placePiece(Piece piece, Square square)
{
    Bitboard::setBit(piecesBitboards[(piece > WHITE_KING) ? (piece - 6) : piece], square);
    Bitboard::setBit(colorBitboards[(piece > WHITE_KING) ? 1 : 0], square);
    Bitboard::setBit(piecesBitboards[ALL_PIECES], square);
    board[square] = piece;
}

inline void Position::removePiece(Square square)
{
    Bitboard::resetBit(piecesBitboards[(board[square] > WHITE_KING) ? (board[square] - 6) : board[square]], square);
    Bitboard::resetBit(colorBitboards[(board[square] > WHITE_KING) ? 1 : 0], square);
    Bitboard::resetBit(piecesBitboards[ALL_PIECES], square);
    board[square] = NO_PIECE;
}