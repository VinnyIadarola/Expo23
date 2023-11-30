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

// This will be moves to another file but will still be global
//  Interfile variable
piece_t board[8][8];

// Global variables
position_t whiteKing;
position_t blackKing;
// this requires discussion mainly runtime checking to see how intensive it is to run through the data
position_t kingMoves[3][3];

// The line along that we being checked so we can see if there are any valid moves that can block
position_t checkVector[6];
// Block is only a valid move if there is only one thing putting us in
int checkAmnt = 0;

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

    // Sets up extra king data
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            kingMoves[i][j].col = -1;
            kingMoves[i][j].col = -1;
        }
    }

    blackKing.row = 7;
    kingMoves[1][1].col = whiteKing.col = blackKing.col = 4;
    kingMoves[1][1].row = whiteKing.row = 0;
    whiteKing.attacked = blackKing.attacked = false;
}

// SIGNIFY UNUSED SPOTS WITH signify unused spots with .row/.col = -1.
// ALSO TREAT THE KING AS AN EMPTY AND KEEP MOVING THROUGH WHEN YOU FIND IT
// it makes my king job alot easier for not alot of work
/**
 * @brief Pawn Max
 *
 * @return *position_t
 */
// Pawn
static void validPawnMoves(int row, int col, position_t moveset[28])
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
static void validKnightMoves(int row, int col, position_t moveset[28])
{
    // Implement knight-specific logic
    return NULL;
}

/**
 * @brief Bishop BEN
 *
 * @return *position_t
 */
static void validBishopMoves(int row, int col, position_t moveset[28])
{
    // Implement bishop-specific logic
    return NULL;
}

/**
 * @brief Rook KEVIN
 *
 * @return *position_t
 */
static void validRookMoves(int row, int col, position_t moveset[28])
{
    // Implement rook-specific logic
    return NULL;
}

/**
 * @brief Queen MAX
 *
 * @return *position_t
 */
static void validQueenMoves(int row, int col, position_t moveset[28])
{
    // Implement queen-specific logic
    return NULL;
}

/**
 * @brief checks if the sides of the currrent side's row is being attack or not
 * to determine if its castable. The first bool value is the west side castle and
 * second is the east side
 *
 * @return true if castle is a valid move
 * @return false if castling is not a vlid move
 */

static void kingCastable(bool kingColor, bool castle[2])
{
    return {false, false};
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
void getValidMoves(int row, int col, position_t moveset[28])
{
    kingCastable();
}

/**
 * @brief this edits a 2d array that contains all the potential moves a king could make on the chessboard
 * so that it will no go off the board. does not check if it is being attacked
 *
 * @param kingColor the current king be evaulated
 * @param moveset the array that will be generated with valid moves
 */
static void getKingPotentialMoves(bool kingColor, position_t moveSet[3][3])
{
    // Determines which king's position to use
    position_t *activeKing = (kingColor) ? &whiteKing : &blackKing;

    // Nested for loop to go through the 2d array of possible king positions
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Calculates actual row/col values that will be used for the moveSet
            int row = activeKing->row - 1 + i;
            int col = activeKing->col - 1 + j;

            if (row >= 0 && row <= 7 && col >= 0 && col <= 7 && (board[row][col].piece_type == EMPTY || board[row][col].color != kingColor))
            {
                // valid move with no piece in the way
                moveSet[i][j].row = row;
                moveSet[i][j].col = col;
            }
            else
            {
                // Invalid move because it's out of bounds or occupied
                moveSet[i][j].row = -1;
                moveSet[i][j].col = -1;
            }
        }
    }
}

/**
 * @brief Runs through two arrays of position_t and compares each value looking for a match. If there is a
 * match sets the kingMoveSet position at the match .attacked = true. If this position also is the king's
 * position it will increment the amount of checks counter and for the first check calculates the vector
 * between them.
 *
 * @param attackingMoveSet the move set of the current turns peice
 * @param kingMoveSet the king that is being evaulated and
 */
static void compareMoveLists(position_t attackingMoveSet[28], position_t kingMoveSet[9])
{

    // Outer Comparison for the attackingMoveSet array
    for (int i = 0; i < 28; i++)
    {
        // When we reach unused positions, break out to stop comparing
        if (attackingMoveSet[i].row == -1)
        {
            break;
        }

        // Run through the king moves to see if theres a match
        for (int j = 0; j < 9; j++)
        {
            // If this is an invalid king position or these positions dont match continue to next position
            if (kingMoveSet[j].row == -1 || !isMatchingPosition(kingMoveSet[j], attackingMoveSet[i]))
            {
                continue;
            }

            // the king position matched so it is being attacked
            kingMoveSet[j].attacked = true;
            // If we are looking at the king position then checkAmnt increases
            if (j == 4 && checkAmnt++ == 0)
            {
                // Only run this for the first time checked
                getCheckVector(attackingMoveSet[i], kingMoveSet[j]);
            }
        }
    }
}

/**
 * @brief Checks if two given position structs have the same row and col values
 *
 * @param pos1 the first position given that will be compared
 * @param pos2 the second position given that will be compared
 * @return true if the positions are identical
 * @return false if the positions are not identical
 */
static bool isMatchingPosition(position_t pos1, position_t pos2)
{
    return pos1.col == pos2.col && pos1.row == pos2.row;
}

/**
 * @brief given an attacker position and king position determines the direction of the vector
 * (whether it needs to go east to west/north to south) then calculates the total distance it
 * needs to travel to reach the point. This sets the global variable checkVector.
 *
 * @param attacker the peice putting the king in check's position
 * @param king the king's position
 */
static void getCheckVector(position_t attacker, position_t king)
{

    // Determines the unit vector in which the check vector moves
    int rowDirection = (king.row > attacker.row) ? 1 : (king.row < attacker.row) ? -1
                                                                                 : 0;
    int colDirection = (king.col > attacker.col) ? 1 : (king.col < attacker.col) ? -1
                                                                                 : 0;
    // Determines the distance needed to covor along the path from the king to attacker
    int distance = max(abs(king.row - attacker.row), abs(king.col - attacker.col));

    for (int i = 0; i < distance; i++)
    {
        checkVector[i].row = attacker.row + i * rowDirection;
        checkVector[i].col = attacker.col + i * colDirection;
    }
}

/**
 * @brief Set the Discover Check Flags of the peices in the board for later use when determining movement
 * Goes through the 8 intercardinal directions until it finds the first peice and if that peice is allied
 * sets it flag
 *
 * @param kingColor the current team thats being checked
 */
static void setDiscoverCheckFlags(bool kingColor)
{
    position_t *activeKing = (kingColor) ? &whiteKing : &blackKing;
    int kingRow = activeKing->row;
    int kingCol = activeKing->col;

    // Direction in terms of unit vectors
    int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (int k = 0; k < 8; k++)
    {
        int dRow = directions[k][0];
        int dCol = directions[k][1];

        for (int step = 1; step < 8; step++)
        {
            int row = kingRow + step * dRow;
            int col = kingCol + step * dCol;

            // Out of bounds
            if (row < 0 || row >= 8 || col < 0 || col >= 8)
            {
                break;
            }

            // Empty position
            if (board[row][col].piece_type == EMPTY)
            {
                continue;
            }

            // This directions allied peice found next intercardinal direction
            if (board[row][col].color == kingColor)
            {
                board[row][col].discover_check = true;
                break;
            }

            // Enemy peice found will be handled when finding checks next intercardinal direction
            if (board[row][col].color != kingColor)
            {
                break;
            }
        }
    }
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
    // position_t potentialMoves[3][3]; unsed for now since its a global variable
    position_t attackingMoves[28];

    // Sets the global var kingMoves to hold all logically valid positions
    getKingPotentialMoves(kingColor, kingMoves);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // If board has no peices skip over it
            if (board[i][j].piece_type == EMPTY || board[i][j].color == kingColor)
            {
                continue;
            }

            // Position is occupied by opposing team so get the attackers moveset
            getValidMoves(i, j, attackingMoves);

            // Check for any matches between attacking and king positions
            compareMoveLists(attackingMoves, kingMoves);
        }
    }

    // Set allied peices that'd result in a discover check
    setDiscoverCheckFlags(kingColor);
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

game_state_t checkGamOver()
{
    checkStalemate();
    return CHESS;
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
