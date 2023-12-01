
#include "ChessLibrary.h"
#include <stdlib.h>
#include <time.h>

void randomChessBoard()
{
    // Initialize random seed
    srand(time(NULL));

    // Define the types of pieces available
    chess_piece_name_t pieces[] = {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN, EMPTY};

    // Counters for each piece type for both colors
    int blackPieceCount[] = {0, 0, 0, 0, 0, 0, 0}; // Corresponds to pieces array
    int whitePieceCount[] = {0, 0, 0, 0, 0, 0, 0}; // Corresponds to pieces array
    int maxPieceCount[] = {1, 1, 2, 2, 2, 8, 64};  // Maximum number of each piece for each color

    // Iterate over the chess board and assign random pieces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int pieceIndex, color;
            do
            {
                // Randomly choose a piece and its color
                pieceIndex = rand() % (sizeof(pieces) / sizeof(pieces[0]));
                color = rand() % 2;

                // Check for pawn placement constraints
                if (pieces[pieceIndex] == PAWN && ((i == 0 && color == 0) || (i == 7 && color == 1)))
                {
                    continue;
                }
            } while ((color == 0 && blackPieceCount[pieceIndex] >= maxPieceCount[pieceIndex]) ||
                     (color == 1 && whitePieceCount[pieceIndex] >= maxPieceCount[pieceIndex]));

            // Place the piece and update count
            board[i][j].piece_type = pieces[pieceIndex];
            if (color == 0)
            {
                blackPieceCount[pieceIndex]++;
            }
            else
            {
                whitePieceCount[pieceIndex]++;
            }

            // Assign the color
            board[i][j].color = color;

            // Assign random special status
            board[i][j].special_status = rand() % 2;
            board[i][j].discover_check = rand() % 2;
        }
    }
}

// Function to get the abbreviated piece name
const char *getPieceAbbreviation(chess_piece_name_t piece)
{
    switch (piece)
    {
    case KING:
        return "K";
    case QUEEN:
        return "Q";
    case ROOK:
        return "R";
    case KNIGHT:
        return "N"; // 'N' for 'Knight' to avoid confusion with 'King'
    case BISHOP:
        return "B";
    case PAWN:
        return "P";
    case EMPTY:
        return ". ";
    default:
        return "?";
    }
}

// Function to print the chessboard
void printChessBoard()
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d ", 1 + i); // Print the row number
        for (int j = 0; j < 8; j++)
        {
            const char *abbreviation = getPieceAbbreviation(board[i][j].piece_type);
            char colorChar = (board[i][j].color) ? 'w' : 'b';
            if (board[i][j].piece_type == EMPTY)
            {
                printf("%s ", abbreviation); // Print empty square
            }
            else
            {
                printf("%c%s ", colorChar, abbreviation); // Print piece with color
            }
        }
        printf("\n");
    }
    printf("  a  b  c  d  e  f  g  h\n");
}

int main(void)
{
    chessboardInit();
    printChessBoard();
}
