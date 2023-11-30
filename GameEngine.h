/**
 * @file ChessEngine.h
 * @author Vincent Iadarola KHK Expo
 * @brief to do
 * @version 0.1
 * @date 2023-11-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "ChessLibrary.h"

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

uint8_t whiteMin;
uint8_t whiteSec;
uint8_t blackMin;
uint8_t blackSec;

bool currTurn;

void pollForMove();
void waitMove();
void turnOnLights(position_t *lightArray);
void displayBadMove();
void setTimers();

#endif