/**
 * @file ChessLibrary.c
 * @author Vinceent Iadarola KHK Expo
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "ChessLibrary.h"

piece_t board[8][8];
bool currTurn = true;

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
                board[i][j].special_moves = FIRST_MOVE
            }
            else if (i >= 6)
            {
                board[i][j].color = false;
                board[i][j].special_moves = FIRST_MOVE
            }
            else
            {
                board[i][j] = EMPTY;
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