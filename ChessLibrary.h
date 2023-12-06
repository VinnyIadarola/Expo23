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
#ifndef __CHESSLIBRARY_H__
#define __CHESSLIBRARY_H__

#include "GameEngine.h"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

typedef struct
{
    uint8_t row;
    uint8_t col;
    bool attacked;
} position_t;

typedef enum
{
    EN_PASSANTABLE,
    FIRST_MOVE,
    NONE, 
} special_moves_t;

typedef struct
{
    chess_piece_name_t piece_type;
    bool color;
    special_moves_t special_status;

    // Will be one of these to denote directions {rowdir, coldir} set to {0,0} after turn
    // This is direction from king to allied peice
    //{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int discover_check_uv[2];
} piece_t;

extern piece_t board[8][8];

void chessboardInit();

void getValidMoves(int row, int col, position_t moveset[28]);

void kingStatus(bool kingColor);

game_state_t checkGameOver();

position_t pawnPromotions();

#endif