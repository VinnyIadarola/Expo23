/**
 * @file ChessLibrary.h
 * @author Vincent Iadarola KHK Expo
 * @brief to do
 * @version 0.1
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "GameEngine.h"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

move_t movelist[27];
bool currTurn;

/**
 * @brief This enum contains every piece type for a chessboard/checkers game
 * an empty square will be notated by the EMPTY enum then all other values
 * should be ignored
 *
 */
typedef enum
{
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
    EMPTY,
} chess_piece_name_t;

/**
 * @brief This enum clarifies which game state the baord is currently running
 *
 */
typedef enum
{
    CHESS,
    WHITE_WINS,
    BLACK_WINS,
    STALEMATE,
} game_state_t;

/**
 * @brief The special_moves_t is an enum to help determine special case moves in the game running. In chess these cases inlcude en passant,
 * the double pawn move, and castling. In checkers this would be a promoted piece.
 *
 */
typedef enum
{
    EN_PASSANTABLE,
    FIRST_MOVE,
    // REDUNDANT BUT COULD HELP READABILITY
    CASTLEABLE,
} special_moves_t;

/**
 * @brief The piece_t holds basic peice information to help determine what properties it has in the game.
 *
 */
typedef struct
{
    chess_piece_name_t piece_type;
    // White is true
    bool color;

    special_moves_t special_status;
    // If peice is in your kings safe gaurd vectors
    bool discover_check;
} piece_t;

/**
 * @brief The move_t struct helps pass information to the firmware
 *
 */
typedef struct
{
    uint8_t row;
    uint8_t col;
    bool isAttacking;
} move_t;

void chessboardInit();

move_t *getValidMoves(int row, int col);

/**
 * @brief Checks if any enemy pieces can move into the 3x3 array around the king
 * and sets discovered checks flags in the king's outgoing vectors to set discoverCheck
 * flags.
 *
 * @return true
 * @return false
 */
bool *kingStatus();

game_state_t checkGamOver();

move_t pawnPromotions();
