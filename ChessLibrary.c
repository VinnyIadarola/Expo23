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

// Should lower global var amount but thatll come when we start implementing methods but we dont have a stack so yk how it is

// Interfile variable
piece_t board[8][8];

// Global variables
position_t whiteKing;
position_t blackKing;

// The line along that we being checked so we can see if there are any valid moves that can block
position_t checkVector[6];
// Block is only a valid move if there is only one thing putting us in
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

// SIGNIFY UNUSED SPOTS WITH signify unused spots with .row/.col = -1.

/**
 * @brief Pawn Max
 *
 * @return *position_t
 */
// Pawn
static position_t *validPawnMoves(int row, int col, bool currTurn, position_t moveset[28])
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
static position_t *validKnightMoves(int row, int col, bool currTurn, position_t moveset[28])
{
    // Implement knight-specific logic
    return NULL;
}

/**
 * @brief Bishop BEN
 *
 * @return *position_t
 */
static position_t *validBishopMoves(int row, int col, bool currTurn, position_t moveset[28])
{
    // Implement bishop-specific logic
    return NULL;
}

/**
 * @brief Rook KEVIN
 *
 * @return *position_t
 */
static position_t *validRookMoves(int row, int col, bool currTurn, position_t moveset[28])
{
    // Implement rook-specific logic
    return NULL;
}

/**
 * @brief Queen MAX
 *
 * @return *position_t
 */
static position_t *validQueenMoves(int row, int col, bool currTurn, position_t moveset[28])
{
    // Implement queen-specific logic
    return NULL;
}

/**
 * @brief Get the Valid Moves piece at row col MICHAEL AND BEN the max size of a moveset will
 * be 28
 *
 *
 * @param row
 * @param col
 * @return *position_t
 */
position_t *getValidMoves(int row, int col, bool currTurn)
{
    kingCastable();
}

/**
 * @brief checks if the sides of the currrent side's row is being attack or not
 * to determine if its castable. The first bool value is the west side castle and
 * second is the east side
 *
 * @return true if castle is a valid move
 * @return false if castling is not a vlid move
 */
static bool *kingCastable(bool kingColor)
{
    return {false, false};
}

/**
 * @brief Checks if any enemy pieces can move into the 3x3 array around the king
 * and sets discovered checks flags in the king's outgoing vectors to set discoverCheck
 * flags.
 *
 * @param kingColor
 */
void kingStatus(bool kingColor)
{
    position_t potentialMoves[3][3];
    getKingPotentialMoves(kingColor, potentialMoves);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // If board has no peices skip over it
            if (board[i][j].piece_type == EMPTY)
            {
                continue;
            }
            else
            {
            }
        }
    }
}

/**
 * @brief this edits a 2d array that contains all the potential moves a king could make on the chessboard
 * so that it will no go off the board. However, this does not check if there is currently a piece in that position
 * or if it is being attacked
 *
 * @param kingColor the current king be evaulated
 * @param moveset the array that will be generated with valid moves
 */
static void getKingPotentialMoves(bool kingColor, position_t moveset[3][3])
{

    position_t *activeKing = (kingColor) ? &whiteKing : &blackKing;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int row = activeKing->row - 1 + i;
            int col = activeKing->col - 1 + j;

            if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
            {
                moveset[i][j].row = row;
                moveset[i][j].col = col;
            }
            else
            {
                moveset[i][j].row = -1;
                moveset[i][j].col = -1;
            }
        }
    }
}

/**
 * @brief Get the Check Vector object
 *
 * @param row
 * @param col
 * @return position_t*
 */
static position_t *getCheckVector(int row, int col)
{
}

static void setDiscoverCheckFlags()
{
}

game_state_t checkGamOver()
{
    checkStalemate();
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

/**
 * @brief checks if the northmost and southern most rows contain any pawns
 * that need to promote
 *
 * @return position_t
 */
position_t pawnPromotions()
{
    return nullptr;
}

/**
 * Check Draw - a player makes the same move three times in a row
 */
static game_state_t checkDraw()
{
    static position_t prevMove;
}
