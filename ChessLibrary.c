/**
 * @file ChessLibrary.c
 * @author Vincent Iadarola KHK Expo
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "ChessLibrary.h"

piece_t board[8][8];
bool kingMoves[3][3];
bool currTurn = true;
position_t movelist[27];
position_t whiteKing;
position_t blackKing;

// The line along that we being checked so we can see if there are any valid moves that can block
position_t checkVector[6];
// Block is only a valid move if there is only one thing putting us in check
bool singleCheck;

/**
 * @brief This function initialize the board to be the start of a chess match
 * white peices are row < 1 and Black peices are row > 6
 *
 */
void chessboardInit()
{
    // Clears current board of any potential pieces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            if (i <= 1)
            {
                board[i][j].color = true;
                board[i][j].special_status = FIRST_MOVE;
            }
            else if (i >= 6)
            {
                board[i][j].color = false;
                board[i][j].special_status = FIRST_MOVE;
            }
            else
            {
                board[i][j].piece_type = EMPTY;
            }
        }
    }

    // Set up the pawns
    for (int i = 0; i < 8; i++)
    {
        // White pawns
        board[1][i].piece_type = PAWN;

        // Black pawns
        board[6][i].piece_type = PAWN;
    }

    // Setting up peices
    board[0][0].piece_type = board[0][7].piece_type = board[7][0].piece_type = board[7][7].piece_type = ROOK;
    board[0][1].piece_type = board[0][6].piece_type = board[7][1].piece_type = board[7][6].piece_type = KNIGHT;
    board[0][2].piece_type = board[0][5].piece_type = board[7][2].piece_type = board[7][5].piece_type = BISHOP;
    board[0][3].piece_type = board[7][3].piece_type = QUEEN;
    board[0][4].piece_type = board[7][4].piece_type = KING;
}

/**
 * @brief Pawn Max
 *
 * @return *position_t
 */
// Pawn
static *position_t validPawnMoves()
{
    // Implement pawn-specific logic
    return NULL;
}

/**
 * @brief Knight Michael
 *
 * @return *position_t
 */
// Knight
static *position_t validKnightMoves()
{
    // Implement knight-specific logic
    return NULL;
}

/**
 * @brief Bishop BEN
 *
 * @return *position_t
 */
static *position_t validBishopMoves()
{
    // Implement bishop-specific logic
    return NULL;
}

/**
 * @brief Rook KEVIN
 *
 * @return *position_t
 */
static *position_t validRookMoves()
{
    // Implement rook-specific logic
    return NULL;
}

/**
 * @brief Queen MAX
 *
 * @return *position_t
 */
static *position_t validQueenMoves()
{
    // Implement queen-specific logic
    return NULL;
}

/**
 * @brief Checks if any enemy pieces can move into the 3x3 array around the king
 * and sets discovered checks flags in the king's outgoing vectors to set discoverCheck
 * flags.
 *
 * @return true
 * @return false
 */
*bool kingStatus(bool color)
{
    return {{false, false, false}, {false, false, false}, {false, false, false}};
}

/**
 * @brief Get the Valid Moves piece at row col MICHAEL AND BEN
 *
 * @param row
 * @param col
 * @return *position_t
 */
static *position_t getValidMoves(int row, int col)
{
}

/**
 * @brief Get the Check Vector object
 *
 * @param row
 * @param col
 * @return *position_t
 */
static *position_t getCheckVector(int row, int col){

}

    /**
     * @brief checks if the sides of the currrent side's row is being attack or not
     * to determine if its castable. The first bool value is the west side castle and
     * second is the east side
     *
     * @return true if castle is a valid move
     * @return false if castling is not a vlid move
     */
    * bool kingCastable(bool color)
{
    return {false, false};
}

game_state_t checkGamOver()
{
    return CHESS;
}

/**
 * @brief call if the king has no moves other than the center to check if other peices
 * can move
 *
 * @return game_state_t
 */
static game_state_t checkStalemate()
{
    return STALEMATE;
}

static void setKingDiscoverKing()
{
}

/**
 * @brief checks if the northmost and southern most rows contain any pawns
 * that need to promote
 *
 * @return position_t
 */
position_t pawnPromotions()
{
    return NULL;
}

/**
 * Check Draw - a player makes the same move three times in a row
 */
static game_state_t checkDraw()
{
}
