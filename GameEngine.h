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

#include "ChessLibrary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t whiteMin;
uint8_t whiteSec;
uint8_t blackMin;
uint8_t blackSec;

void pollForMove();
void waitMove();
void turnOnLights(position_t *lightArray);
void displayBadMove();
void setTimers();
