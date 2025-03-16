#include "perft.hpp"

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

namespace Perft
{
MagicBitboard magicBitboardP;
MoveGen       moveGenP;

const std::vector<PerftTest> TEST_POSITIONS = {
    {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6, 119060324, "Initial Position"},
    {"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", 4, 4085603, "Kiwipete"},
    {"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", 5, 674624, "Endgame Position"},
    {"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 4, 422333, "Castle Rights Test"},
    {"rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8", 4, 2103487, "Promotion Test"},
    {"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", 4, 3894594, "En Passant Test"},
    {"n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1", 4, 182838, "Test"}};

void generateAllLegalMoves(Position& position, std::vector<Move>& moves)
{
    std::array<Piece, SQUARE_NB> board = position.getBoard();

    uint64_t allPiecesBitboard = position.getPieceBitboard(ALL_PIECES);
    while (allPiecesBitboard)
    {
        Square sq = static_cast<Square>(Bitboard::getLSB(allPiecesBitboard));
        allPiecesBitboard &= allPiecesBitboard - 1;

        Piece piece = board[sq];

        Color pieceColor = (piece <= WHITE_KING) ? WHITE : BLACK;
        if (pieceColor != position.getSideToMove()) { continue; }

        if (piece == WHITE_PAWN || piece == BLACK_PAWN)
        {
            moveGenP.generatePawnMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
        else if (piece == WHITE_ROOK || piece == BLACK_ROOK)
        {
            moveGenP.generateRookMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
        else if (piece == WHITE_KNIGHT || piece == BLACK_KNIGHT)
        {
            moveGenP.generateKnightMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
        else if (piece == WHITE_BISHOP || piece == BLACK_BISHOP)
        {
            moveGenP.generateBishopMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
        else if (piece == WHITE_QUEEN || piece == BLACK_QUEEN)
        {
            moveGenP.generateQueenMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
        else if (piece == WHITE_KING || piece == BLACK_KING)
        {
            moveGenP.generateKingMoves(position, static_cast<Square>(sq), pieceColor, moves);
        }
    }

    moves.erase(
        std::remove_if(moves.begin(), moves.end(), [&position](const Move& move) { return !position.isLegal(move); }),
        moves.end());
}

uint64_t perftInternal(Position& position, int depth)
{
    std::vector<Move> moves;
    moves.reserve(218);

    if (depth == 1)
    {
        generateAllLegalMoves(position, moves);
        return moves.size();
    }

    generateAllLegalMoves(position, moves);
    uint64_t nodes = 0;

    for (const Move& move : moves)
    {
        StateInfo newState;
        position.makeMove(move, newState);
        nodes += perftInternal(position, depth - 1);
        position.undoMove();
    }

    return nodes;
}

uint64_t perft(Position& position, int depth, std::vector<Move>& moves) { return perftInternal(position, depth); }

void runPerftTests()
{
    auto squareToAlgebraic = [](int square) -> std::string {
        const char file = 'a' + (square % 8);
        const char rank = '1' + (square / 8);
        return std::string(1, file) + std::string(1, rank);
    };

    auto formatNumber = [](uint64_t n) -> std::string {
        std::string s              = std::to_string(n);
        int         insertPosition = s.length() - 3;
        while (insertPosition > 0)
        {
            s.insert(insertPosition, ",");
            insertPosition -= 3;
        }
        return s;
    };

    for (const auto& test : TEST_POSITIONS)
    {
        Position position;
        position.loadFen(test.fen);

        std::cout << "Testing: " << test.description << "\n";
        std::cout << "FEN: " << test.fen << "\n";
        std::cout << "Depth: " << test.depth << "\n";

        auto     start = std::chrono::high_resolution_clock::now();
        uint64_t nodes = perftInternal(position, test.depth);
        auto     end   = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Nodes: " << formatNumber(nodes) << "\n";
        std::cout << "Expected: " << formatNumber(test.expected_nodes) << "\n";
        std::cout << "Time: " << duration.count() << "ms\n";
        std::cout << "Nodes/second: " << formatNumber(nodes * 1000 / duration.count()) << "\n";

        if (nodes == test.expected_nodes) { std::cout << "Result: PASS\n"; }
        else
        {
            std::cout << "Result: FAIL\n";
            std::cout << "\nDivide Perft Analysis for depth " << test.depth << ":\n";
            dividePerft(position, test.depth);
        }
        std::cout << '\n';
    }
}

void dividePerft(Position& position, int depth)
{
    std::vector<Move> moves;
    moves.reserve(218);
    generateAllLegalMoves(position, moves);

    uint64_t total = 0;
    for (const Move& move : moves)
    {
        StateInfo newState;
        position.makeMove(move, newState);
        uint64_t nodes = perftInternal(position, depth - 1);
        position.undoMove();

        std::cout << move.toString() << ": " << nodes << "\n";
        total += nodes;
    }
    std::cout << "\nTotal: " << total << " nodes\n";
}

}  // namespace Perft