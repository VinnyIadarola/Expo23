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
#define max(a, b) ((a) > (b) ? (a) : (b))

// This will be moves to another file but will still be global
//  Interfile variable
piece_t board[8][8];

// Global variables
position_t whiteKing;
position_t blackKing;
// this requires discussion mainly runtime checking to see how intensive it is to run through the data
position_t kingMoves[3][3];

// The line along that we being checked so we can see if there are any valid moves that can block
// should include piece make 7
position_t checkVector[7];
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

    // Setting up pieces
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

    // Verify that the moving piece is a pawn
    if (board[row][col].piece_type != PAWN)
    {
        return;
    }

    // Check if discover check unit vector is diagonal. Will help in determining if the moving piece is pinned or not
    int unitVector[2] = board[row][col].discover_check_uv;
    bool isUnitVectorDiagonal = false;
    if ((unitVector[0] == -1 || unitVector[0] == 1) && (unitVector[1] == -1 || unitVector[1] == 1))
    {
        isUnitVectorDiagonal = true;
    }

    // Check if moving piece is pinned
    bool isPinned = false;
    bool breakOuterLoop = false;
    int pinningPieceRow;
    int pinningPieceCol;
    for (int i = col; i >= 1 && i <= 8 && !breakOuterLoop; i + unitVector[0])
    {
        for (int j = row; j >= 1 && j <= 8; j + unitVector[1])
        {
            if (board[i][j].piece_type == QUEEN && board[i][j].color != board[row][col].color)
            {
                isPinned = true;
                breakOuterLoop = true;
                pinningPieceCol = i;
                pinningPieceRow = j;
                break;
            }
            else if (board[i][j].piece_type == BISHOP && board[i][j].color != board[row][col].color && isUnitVectorDiagonal)
            {
                isPinned = true;
                breakOuterLoop = true;
                pinningPieceCol = i;
                pinningPieceRow = j;
                break;
            }
            else if (board[i][j].piece_type == ROOK && board[i][j].color != board[row][col].color && !isUnitVectorDiagonal)
            {
                isPinned = true;
                breakOuterLoop = true;
                pinningPieceCol = i;
                pinningPieceRow = j;
                break;
            }
        }
    }

    int moveIndex = 0; // Counter to track the amout of moves the pawn has
    // Finds valid WHITE pawn moves
    if (board[row][col].color)
    {
        // If square in front of moving piece is unoccupied and the moving piece is not pinned,then moving forward one square is valid
        if (board[row + 1][col].piece_type == EMPTY && !isPinned)
        {
            moveset[moveIndex].row = row + 1;
            moveset[moveIndex].col = col;
            moveIndex++;
        }

        // If square in front of moving piece is unoccupied and square two rows in front of moving piece is unoccupied,
        // and the moving piece is not pinned, and moving pawn has first move status, then moving forward two squares is valid
        if (board[row][col].special_status == FIRST_MOVE)
        {
            if (board[row + 2][col].piece_type == EMPTY && board[row + 1][col].piece_type == EMPTY && !isPinned)
            {
                moveset[moveIndex].row = row + 2;
                moveset[moveIndex].col = col;
                moveIndex++;
            }
        }

        // If moving piece is not on the left edge, then capturing left may be valid
        if (col > 1)
        {
            bool canCapturePinningPieceLeft = false;
            // If the moving piece is pinned, BUT the pinning piece is one square diagonal to the moving piece,
            // then the moving piece can capture the pinning piece
            if (isPinned && pinningPieceRow == row + 1 && pinningPieceCol == col - 1)
            {
                canCapturePinningPieceLeft = true;
            }

            // If there is a black piece one square diagonal to the left of the moving piece, and the moving piece is not pinned,
            // then capturing left is valid. However, if the pinning piece can be captured, then capturing left is valid.
            if ((board[row + 1][col - 1].piece_type != EMPTY && !board[row + 1][col - 1].color && !isPinned) || canCapturePinningPieceLeft)
            {
                moveset[moveIndex].row = row + 1;
                moveset[moveIndex].col = col - 1;
                moveIndex++;
            }
            // If black pawn is En Passantable, and adjacent to moving piece on the 5th row, then moving piece can capture diagonally.
            if (board[5][col - 1].special_status == EN_PASSANTABLE && !isPinned)
            {
                moveset[moveIndex].row = row + 1;
                moveset[moveIndex].col = col - 1;
                moveIndex++;
            }
        }

        // If moving piece is not on the right edge, then capturing right may be valid.
        if (col < 8)
        {
            bool canCapturePinningPieceRight = false;
            if (isPinned && pinningPieceRow == row + 1 && pinningPieceCol == col + 1)
            {
                canCapturePinningPieceRight = true;
            }
            if ((board[row + 1][col + 1].piece_type != EMPTY && !board[row + 1][col + 1].color) || canCapturePinningPieceRight)
            {
                moveset[moveIndex].row = row + 1;
                moveset[moveIndex].col = col + 1;
                moveIndex++;
            }
            if (board[5][col + 1].special_status == EN_PASSANTABLE && !isPinned)
            {
                moveset[moveIndex].row = row + 1;
                moveset[moveIndex].col = col + 1;
                moveIndex++;
            }
        }
    }

    // Finds valid BLACK pawn moves. Only difference is that row number decreases as black pawn traverses the board.
    if (!board[row][col].color)
    {
        if (board[row - 1][col].piece_type == EMPTY && !isPinned)
        {
            moveset[moveIndex].row = row - 1;
            moveset[moveIndex].col = col;
            moveIndex++;
        }
        if (board[row][col].special_status == FIRST_MOVE)
        {
            if (board[row - 2][col].piece_type == EMPTY && !isPinned)
            {
                moveset[moveIndex].row = row - 2;
                moveset[moveIndex].col = col;
                moveIndex++;
            }
        }

        if (col > 1)
        {
            bool canCapturePinningPieceLeft = false;
            if (isPinned && pinningPieceRow == row - 1 && pinningPieceCol == col - 1)
            {
                canCapturePinningPieceLeft = true;
            }

            if ((board[row - 1][col - 1].piece_type != EMPTY && board[row - 1][col - 1].color) || canCapturePinningPieceLeft)
            {
                moveset[moveIndex].row = row - 1;
                moveset[moveIndex].col = col - 1;
                moveIndex++;
            }
            if (board[4][col - 1].special_status == EN_PASSANTABLE && !isPinned)
            {
                moveset[moveIndex].row = row - 1;
                moveset[moveIndex].col = col - 1;
                moveIndex++;
            }
        }

        if (col < 8)
        {
            bool canCapturePinningPieceRight = false;
            if (isPinned && pinningPieceRow == row - 1 && pinningPieceCol == col + 1)
            {
                canCapturePinningPieceRight = true;
            }
            if ((board[row - 1][col + 1].piece_type != EMPTY && board[row - 1][col + 1].color) || canCapturePinningPieceRight)
            {
                moveset[moveIndex].row = row - 1;
                moveset[moveIndex].col = col + 1;
                moveIndex++;
            }
            if (board[4][col + 1].special_status == EN_PASSANTABLE && !isPinned)
            {
                moveset[moveIndex].row = row - 1;
                moveset[moveIndex].col = col + 1;
                moveIndex++;
            }
        }
    }

    // If king is in check, then the only valid pawn moves are the moves that
    // block the check vector OR captures the checking piece (Not yet implemented)
    if (checkAmnt == 1)
    {
        for (int i = 0; i < moveIndex; i++)
        {
            for (int j = 0; j < sizeof(checkVector) / sizeof(checkVector[0]); j++)
            {
                if (moveset[i].row != checkVector[j].row && moveset[i].col != checkVector[j].col)
                {
                    moveset[i].row = -1;
                    moveset[i].col = -1;
                }
            }
        }
    }

    // Sets the row and col of all unused spots to -1
    for (int i = moveIndex; i < sizeof(moveset) / sizeof(moveset[0]); i++)
    {
        moveset[i].row = -1;
        moveset[i].col = -1;
    }

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
    // Knight has 8 possible unique moves
    // Check if the current position of knight allows for such moves
    int move_index = 0; // counter to track the index of valid moves this knight has
    // if checkamnt is 0 the piece can freely move, if its 1 compare the moveset with check vector, and if its > 1 return current position

    bool color = board[row][col].color;

    if (checkAmnt > 1)
    {
        moveset[0].row = row;
        moveset[0].col = col;
        moveset[1].row = -1;
        moveset[1].col = -1;
        return;
    }

    // Two forward, one left
    if (row >= 2 && col >= 1)
    {
        row = row - 2;
        col = col - 1;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].color != color)
        {
            moveset[move_index].attacked = true;
        }
        else
        {
            moveset[move_index].attacked = false;
        }
    }
    // Two forward, one right
    if (row >= 2 && col <= 6)
    {
        row = row - 2;
        col = col + 1;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].color != color)
        {
            moveset[move_index].attacked = true;
        }
        else
        {
            moveset[move_index].attacked = false;
        }
    }
    // Two backward, one left
    if (row <= 5 && col >= 1)
    {
        row = row + 2;
        col = col - 1;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }
    // Two backward, one right
    if (row <= 5 && col <= 6)
    {
        row = row + 2;
        col = col + 1;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }

    // Two left, one forward
    if (col >= 2 && row >= 1)
    {
        row = row - 1;
        col = col - 2;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }
    // Two right, one forward
    if (col <= 5 && row >= 1)
    {
        row = row - 1;
        col = col + 2;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }
    // Two left, one backward
    if (col >= 2 && row <= 6)
    {
        row = row + 1;
        col = col - 2;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }
    // Two right, one backward
    if (col <= 5 && row <= 6)
    {
        row = row + 1;
        col = col + 2;
        moveset[move_index].row = row;
        moveset[move_index].col = col;
        move_index++;
        if (board[row][col].piece_type == EMPTY || board[row][col].color == color)
        {
            moveset[move_index].attacked = false;
        }
        else
        {
            moveset[move_index].attacked = true;
        }
    }

    moveset[move_index].row = -1;
    moveset[move_index].col = -1;

    if (checkAmnt == 1)
    {
        for (int i = 0; i < move_index; i++)
        {
            for (int j = 0; j < (int)sizeof(checkVector); j++)
            {
                if (checkVector[j].row != moveset[i].row && checkVector[j].col != moveset[i].col)
                {
                    moveset[i].row = -1;
                    moveset[i].col = -1;
                }
            }
        }
    }

    return NULL;
}

/**
 * @brief Bishop
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
    // Rook has a max of 16 total moves
    // Check if the current position of the Rook allows for such moves
    int move_index = 0; // counter to track the index of valid moves this Rook has
    // if checkAmnt is 0, the piece can freely move, if it's 1 compare the moveset with check vector, and if its > 1 return current position

    // Case if checkAmnt bigger than 1
    if (checkAmnt > 1)
    {
        moveset[0].row = row;
        moveset[0].col = col;
        return;
    }

    // Valid moves of Rook
    // Traverse along unit vector {0, 7}
    for (int i = 0; i < 8; i++)
    {
        // for the horizontal valid moves; row
        if (board[row][i].piece_type != EMPTY)
        {
            if (board[row][i].color != board[row][col].color)
            {
                moveset[moveIndex].row = row;
                moveset[moveIndex].col = i;
                moveIndex++;
                break;
            }
            else
            {
                break;
            }
        }
        else if (board[row][i].piece_type == EMPTY)
        {
            moveset[moveIndex].row = row;
            moveset[moveIndex].col = i;
            moveIndex++;
        }

        // for the vertical valid moves; column
        if (board[i][col].piece_type != EMPTY)
        {
            if (board[i][col].color != board[row][col].color)
            {
                moveset[moveIndex].row = i;
                moveset[moveIndex].col = col;
                moveIndex++;
                break;
            }
            else
            {
                break;
            }
        }
        else if (board[i][col].piece_type == EMPTY)
        {
            moveset[moveIndex].row = i;
            moveset[moveIndex].col = col;
            moveIndex++;
        }
    }

    // Case if checkAmnt is 1
    if (checkAmnt == 1)
    {
        for (int i = 0; i < move_index; i++)
        {
            for (int j = 0; j < (int)sizeof(checkVector); j++)
            {
                if (checkVector[j].row == moveset[i].row && checkVector[j].col == moveset[i].col)
                {
                    moveset[i].row = NULL;
                    moveset[i].col = NULL;
                }
            }
        }
    }

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

    if (board[row][col].piece_type != QUEEN)
    {
        return;
    }

    int moveIndex = 0;
    // Traverse along unit vector {1, 0}
    for (int i = col; i <= 8; i++)
    {
        if (board[row][i].piece_type != EMPTY)
        {
            if (board[row][i].color != board[row][col].color)
            {
                moveset[moveIndex].row = row;
                moveset[moveIndex].col = i;
                moveIndex++;
                break;
            }
            else
            {
                break;
            }
        }
        else if (board[row][i].piece_type == EMPTY)
        {
            moveset[moveIndex].row = row;
            moveset[moveIndex].col = i;
            moveIndex++;
        }
    }
    // Traverse along unit vector {-1, 0}
    for (int i = col; i >= 1; i--)
    {
        if (board[row][i].piece_type != EMPTY)
        {
            if (board[row][i].color != board[row][col].color)
            {
                moveset[moveIndex].row = row;
                moveset[moveIndex].col = i;
                moveIndex++;
                break;
            }
            else
            {
                break;
            }
        }
        else if (board[row][i].piece_type == EMPTY)
        {
            moveset[moveIndex].row = row;
            moveset[moveIndex].col = i;
            moveIndex++;
        }
    }
    // Traverse along unit vector {0, 1}
    for (int i = row; i <= 8; i++)
    {
        if (board[i][col].piece_type != EMPTY)
        {
            if (board[i][col].color != board[i][col].color)
            {
                moveset[moveIndex].row = i;
                moveset[moveIndex].col = col;
                moveIndex++;
                break;
            }
            else
            {
                break;
            }
        }
        else if (board[i][col].piece_type == EMPTY)
        {
            moveset[moveIndex].row = i;
            moveset[moveIndex].col = col;
            moveIndex++;
        }
    }

    // Traverse along unit vector {0, -1}
    bool breakOuterLoop = false;
    for (int i = row; i >= 1 && !breakOuterLoop; i--)
    {
        if (board[i][col].piece_type != EMPTY)
        {
            if (board[i][col].color != board[i][col].color)
            {
                moveset[moveIndex].row = i;
                moveset[moveIndex].col = col;
                moveIndex++;
                breakOuterLoop = true;
                break;
            }
            else
            {
                breakOuterLoop = true;
                break;
            }
        }
        else if (board[i][col].piece_type == EMPTY)
        {
            moveset[moveIndex].row = i;
            moveset[moveIndex].col = col;
            moveIndex++;
        }
    }
    // Traverse along unit vector {1, 1}
    breakOuterLoop = false;
    for (int i = col; i <= 8 && !breakOuterLoop; i++)
    {
        for (int j = row; j <= 8; j++)
        {
            if (board[j][i].piece_type != EMPTY)
            {
                if (board[j][i].color != board[row][col].color)
                {
                    moveset[moveIndex].row = j;
                    moveset[moveIndex].col = i;
                    moveIndex++;
                    breakOuterLoop = true;
                    break;
                }
                else
                {
                    break;
                    breakOuterLoop = true;
                }
            }
            else if (board[j][i].piece_type == EMPTY)
            {
                moveset[moveIndex].row = j;
                moveset[moveIndex].col = i;
                moveIndex++;
            }
        }
    }

    // Traverse along unit vector {1, -1}
    breakOuterLoop = false;
    for (int i = col; i <= 8 && !breakOuterLoop; i++)
    {
        for (int j = row; j >= 1; j--)
        {
            if (board[j][i].piece_type != EMPTY)
            {
                if (board[j][i].color != board[row][col].color)
                {
                    moveset[moveIndex].row = j;
                    moveset[moveIndex].col = i;
                    moveIndex++;
                    breakOuterLoop = true;
                    break;
                }
                else
                {
                    breakOuterLoop = true;
                    break;
                }
            }
            else if (board[j][i].piece_type == EMPTY)
            {
                moveset[moveIndex].row = j;
                moveset[moveIndex].col = i;
                moveIndex++;
            }
        }
    }

    // Traverse along unit vector {-1, -1}
    breakOuterLoop = false;
    for (int i = col; i >= 1 && !breakOuterLoop; i--)
    {
        for (int j = row; j >= 1; j--)
        {
            if (board[j][i].piece_type != EMPTY)
            {
                if (board[j][i].color != board[row][col].color)
                {
                    moveset[moveIndex].row = j;
                    moveset[moveIndex].col = i;
                    moveIndex++;
                    breakOuterLoop = true;
                    break;
                }
                else
                {
                    breakOuterLoop = true;
                    break;
                }
            }
            else if (board[j][i].piece_type == EMPTY)
            {
                moveset[moveIndex].row = j;
                moveset[moveIndex].col = i;
                moveIndex++;
            }
        }
    }

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
    // return {false, false};
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
    // kingCastable();
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
                // valid move with no piece in the way or enemy piece so you can take (uses short circuiting)
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
 * @param attacker the piece putting the king in check's position
 * @param king the king's position
 */
static void getCheckVector(position_t attacker, position_t king)
{

    // Determines the unit vector in which the check vector moves
    int rowDirection = (king.row > attacker.row) ? 1 : (king.row < attacker.row) ? -1
                                                                                 : 0;
    int colDirection = (king.col > attacker.col) ? 1 : (king.col < attacker.col) ? -1
                                                                                 : 0;
    // Determines the distance needed to cover along the path from the king to attacker
    int distance = max(abs(king.row - attacker.row), abs(king.col - attacker.col));

    for (int i = 0; i < distance; i++)
    {
        checkVector[i].row = attacker.row + i * rowDirection;
        checkVector[i].col = attacker.col + i * colDirection;
    }
}

/**
 * @brief Runs through two arrays of position_t and compares each value looking for a match. If there is a
 * match sets the kingMoveSet position at the match .attacked = true. If this position also is the king's
 * position it will increment the amount of checks counter and for the first check calculates the vector
 * between them.
 *
 * @param attackingMoveSet the move set of the current turns piece
 * @param kingMoveSet the king that is being evaulated and
 */
static void compareMoveLists(position_t attackingMoveSet[28], position_t kingMoveSet[3][3])
{
    // Outer Comparison for the attackingMoveSet array
    for (int i = 0; i < 28; i++)
    {
        // When we reach unused positions, break out to stop comparing
        if (attackingMoveSet[i].row == -1)
        {
            break;
        }

        // Run through the king moves to see if there's a match
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                // If this is an invalid king position or these positions don't match, continue to next position
                if (kingMoveSet[row][col].row == -1 || !isMatchingPosition(kingMoveSet[row][col], attackingMoveSet[i]))
                {
                    continue;
                }

                // The king position matched so it is being attacked
                kingMoveSet[row][col].attacked = true;

                // If we are looking at the king's central position, then checkAmnt increases
                if (row * 3 + col == 4 && checkAmnt++ == 0)
                {
                    // Only run this for the first time checked
                    getCheckVector(attackingMoveSet[i], kingMoveSet[row][col]);
                }
            }
        }
    }
}

/**
 * @brief Set the Discover Check Flags of the pieces in the board for later use when determining movement
 * Goes through the 8 intercardinal directions until it finds the first piece and if that piece is allied
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

            // This directions allied piece found next intercardinal direction
            if (board[row][col].color == kingColor)
            {
                board[row][col].discover_check_uv[0] = directions[k][0];
                board[row][col].discover_check_uv[1] = directions[k][1];
                break;
            }

            // Enemy piece found will be handled when finding checks next intercardinal direction
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
            // If board has no pieces skip over it
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

    // Set allied pieces that'd result in a discover check
    setDiscoverCheckFlags(kingColor);
}

/**
 * @brief call if the king has no moves other than the center to check if other pieces
 * can move
 *
 * @return game_state_t
 */
static game_state_t checkStalemate()
{
    return STALEMATE;
}

game_state_t checkGameOver()
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
    // return nullptr;
}

/**
 * Check Draw - a player makes the same move three times in a row
 */
static game_state_t checkDraw()
{
    static position_t prevMove;
}
