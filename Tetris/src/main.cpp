
#include "raylib.h"
#include <iostream>


//forward declare functions
void AddPieceToBoard(int xPos, int yPos);
void RemovePiece(int xPos, int yPos);
void PrintPiece();
void DrawBoard();
void MoveDown();
void MoveLeft();
void MoveRight();

bool CheckFullRow();
bool CheckMoveDown();
bool CheckMoveRight();
bool CheckMoveLeft();
void RotateRight();

/*
 * Pieces
 */

//height/width of piece
const int pieceWidth = 5;
const int pieceHeight = 5;
//num of piece variants
const int pieceCount = 7;

void GetRandomPiece(int arr[pieceHeight][pieceWidth]);

//array to hold current piece
int piece[pieceHeight][pieceWidth];
//position of current piece
int piecePosX = -100;
int piecePosY = -100;

    int piece0[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    // L Mirrored
    int piece1[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };


    //Square
    int piece2[pieceHeight][pieceWidth] =
    {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0 }
    };

    //Straight
    int piece3[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };

    // Z Mirrored
    int piece4[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // Z 
    int piece5[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // T
    int piece6[pieceHeight][pieceWidth] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

/*
 * Board 
 */

//board size
const int bCols = 10;
const int bRows = 10;
//tile size
int tileWidth = 20;
int tileHeight = 20;
//window size
int windowWidth = bCols * tileWidth;
int windowHeight = bRows * tileHeight;
//board array
char board[bRows][bCols];

/*
 * Score
 */

int score = 0;
bool lost = false;

void main()
{
    //Initialise board array with 0s
    for (int r = 0; r < bRows; r++)
    {
        for (int c = 0; c < bCols; c++)
        {
            board[r][c] = 0;
        }
    }

    //Setup window
    InitWindow(windowWidth, windowHeight, "Tetris");
    SetTargetFPS(30);

    //Start drawing
    BeginDrawing();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        if (lost)
        {
            for (int r = 0; r < bRows; r++)
            {
                for (int c = 0; c < bCols; c++)
                {
                    board[r][c] = 0;
                }
            }

            DrawBoard();

        }
        else
        {
            //if no piece on the board add a piece
            if (piecePosX == -100 && piecePosY == -100)
            {
                piecePosX = bCols / 2;
                piecePosY = 0;
                //std::cout << "No Piece found, adding piece at: " << piecePosX << ", " << piecePosY << "\n";
                GetRandomPiece(piece);
                //PrintPiece();
                AddPieceToBoard(piecePosX, piecePosY);
            }
            //Check for input down
            if (IsKeyDown(KEY_DOWN))
            {
                //std::cout << "Input Detected: Down \n";
                MoveDown();
            }
            //Check for input left
            if (IsKeyDown(KEY_LEFT))
            {
                //std::cout << "Input Detected: Left \n";
                MoveLeft();
            }
            else
                //Check for input right
                if (IsKeyDown(KEY_RIGHT))
                {
                    //std::cout << "Input Detected: Right \n";
                    MoveRight();
                }
                else
                    //Check for input up/rotate
                    if (IsKeyDown(KEY_UP))
                    {
                        //std::cout << "Input Detected: Up \n";
                        RotateRight();
                    }

            DrawBoard();
            //CheckFullRow();
            //MoveDown();
            EndDrawing();

            //check lost
            if (piecePosX == -100 && piecePosY == -100)
            {
                //if no piece check for stuff in the top row of the board
                for (int i = 0; i < bCols && !lost; i++)
                {
                    if (board[0][i] != 0)
                    {
                        std::cout << "Game Lost. Final Score: " << score << ".\n";
                        lost = true;
                    }
                }
            }
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

void AddPieceToBoard(int xPos, int yPos)
{
    for (int r = 0; r < pieceHeight; r++)
    {
        for (int c = 0; c < pieceWidth; c++)
        {
            if (piece[r][c] > 0)
            {
                board[yPos + r][xPos + c] = piece[r][c];
            }
        }
    }
    piecePosX = xPos;
    piecePosY = yPos;
    //std::cout << "Piece Added At: " << piecePosX << ", " << piecePosY << "\n";
}

void RemovePiece(int xPos, int yPos)
{
    for (int r = 0; r < pieceHeight; r++)
    {
        for (int c = 0; c < pieceWidth; c++)
        {
            if (piece[r][c] != 0) //if there is part of the piece here
            {
                board[yPos + r][xPos + c] = 0;
            }
        }
    }
    //reset piece pos
    piecePosX = -100;
    piecePosY = -100;
}

void DrawBoard()
{
    //draw board
    //std::cout << "drawing board \n";
    for (int r = 0; r < bRows; r++)
    {
        for (int c = 0; c < bCols; c++)
        {
            if (board[r][c] == 0)
            {
                DrawRectangle(c * tileWidth, r * tileHeight, tileWidth, tileHeight, BLACK);
            }
            else
            {
                DrawRectangle(c * tileWidth, r * tileHeight, tileWidth, tileHeight, BLUE);
            }
        }
    }
}

bool CheckFullRow()
{
    //std::cout << "Checking for full row \n";
    //check for full row 
    int fRow = -1;
    for (int r = 0; r < bRows && fRow < 0; r++)
    {
        int c = 0;
        while (board[r][c] != 0 && fRow < 0)
        {
            if (c < bCols - 1)
            {
                c++;
            }
            else
            {
                //std::cout << "Full row on row: " << r << "\n";
                fRow = r;
            }

        }
    }
    //clear out the row
    if (fRow >= 0)
    {
        score += 10;
        for (int c = 0; c < bCols; c++)
        {
            board[fRow][c] = 0;
        }

        //move everything down
        for (int r = fRow; r > 0; r--)
        {
            for (int c = 0; c < bCols; c++)
            {
                board[r][c] = board[r - 1][c];
            }
        }
        //clear top row
        for (int c = 0; c < bCols; c++)
        {
            board[0][c] = 0;
        }
        return true;
    }

    return false;
}

bool CheckMoveDown()
{
    for (int r = pieceHeight - 1; r > 0; r--)
    {
        //for each row
        for (int c = 0; c < pieceWidth; c++)
        {
            //if piece found
            if (piece[r][c] != 0)
            {
                if (piecePosY + r == bRows - 1)
                {
                    //std::cout << "piece at edge of board. returning false \n";
                    return false;
                }
                //check if edge
                if (r == pieceHeight || piece[r + 1][c] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + r + 1][piecePosX + c] != 0)
                    {
                        //std::cout << "no space under to piece, returning false \n";
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool CheckMoveLeft()
{
    //std::cout << "Checking CanMoveLeft with piece pos: " << piecePosX << "," << piecePosY << "\n";

    //if more than half off board
    if (piecePosX < (0 - (pieceWidth / 2)))
    {
        //std::cout << "piece at edge of board. returning false \n";
        return false;
    }

    //for each col move down the rows and check for piece
    //when you find the edge of the peice, if it is not at the edge of the board then move it

    //for each col
    for (int c = 0; c < pieceWidth; c++)
    {
        //for each row
        for (int r = 0; r < pieceHeight; r++)
        {
            //if piece found
            if (piece[r][c] != 0)
            {
                if (piecePosX + c == 0)
                {
                    //std::cout << "piece at edge of board. returning false \n";
                    return false;
                }
                //check if edge
                if (c == 0 || piece[r][c - 1] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + r][piecePosX + c - 1] != 0)
                    {
                        //std::cout << "no space next to piece, returning false \n";
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool CheckMoveRight()
{
    //std::cout << "Checking CanMoveRight with piece pos: " << piecePosX << "," << piecePosY << "\n";

    //if more than half off board
    if (piecePosX > (bCols + (pieceWidth / 2)))
    {
        //std::cout << "piece at edge of board. returning false \n";
        return false;
    }

    //for each col move down the rows and check for piece
    //when you find the edge of the peice, if it is not at the edge of the board then move it

    //for each col
    for (int c = pieceWidth - 1; c > 0; c--)
    {
        //for each row
        for (int r = 0; r < pieceHeight; r++)
        {
            //if piece found
            if (piece[r][c] != 0)
            {
                if (piecePosX + c == bCols - 1)
                {
                    //std::cout << "piece at edge of board. returning false \n";
                    return false;
                }
                //check if edge
                if (c == pieceWidth || piece[r][c + 1] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + r][piecePosX + c + 1] != 0)
                    {
                        //std::cout << "no space next to piece, returning false \n";
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void MoveDown()
{
    int xPos = piecePosX;
    int yPos = piecePosY;

    if (CheckMoveDown())
    {
        RemovePiece(piecePosX, piecePosY);

        //DrawBoard();

        yPos++;

        AddPieceToBoard(xPos, yPos);

        //DrawBoard();
    }
    else
    {
        piecePosX = -100;
        piecePosY = -100;
        while (CheckFullRow())
        {
            //row removed
        }
    }
}

void MoveLeft()
{
    int xPos = piecePosX;
    int yPos = piecePosY;
    if (CheckMoveLeft())
    {
        //std::cout << "moving left \n";
        RemovePiece(piecePosX, piecePosY);

        xPos--;

        AddPieceToBoard(xPos, yPos);

    }
}

void MoveRight()
{
    int xPos = piecePosX;
    int yPos = piecePosY;
    if (CheckMoveRight())
    {
        //std::cout << "moving right \n";
        RemovePiece(piecePosX, piecePosY);

        xPos++;

        AddPieceToBoard(xPos, yPos);
    }
}

void RotateRight()
{
    int posX = piecePosX;
    int posY = piecePosY;
    RemovePiece(piecePosX, piecePosY);
    //std::cout << "Rotating piece \n";
    int pieceSize = pieceHeight;
    //std::cout << "Piece at start \n";
    //PrintPiece();
    for (int r = 0; r < pieceSize; r++) 
    {
        for (int c = 0; c < pieceSize - r; c++)
        {
            int temp = piece[r][c];
            piece[r][c] = piece[pieceSize - 1 - c][pieceSize - 1 - r];
            piece[pieceSize - 1 - c][pieceSize - 1 - r] = temp;
        }
    }
    //std::cout << "piece step 1 \n";
    //PrintPiece(); 
    //flip top/bottom
    for (int r = 0; r < pieceSize / 2; r++) {
        for (int c= 0; c < pieceSize; c++) {
            int ptr = piece[r][c];
            piece[r][c] = piece[pieceSize - 1 - r][c];
            piece[pieceSize - 1 - r][c] = ptr;
        }
    }
    //std::cout << "piece at end \n";
    //PrintPiece(); 
    AddPieceToBoard(posX, posY);
    DrawBoard();
}

void PrintPiece()
{
    for (int row = 0; row < pieceHeight; row++)
    {
        for (int col = 0; col < pieceWidth; col++)
        {
            std::cout << piece[row][col] << ", ";
        }
        std::cout << " \n";
    }
}

void GetRandomPiece(int arr[pieceHeight][pieceWidth])
{
    //get random number
    int num = rand() % pieceCount;
    for (int row = 0; row < pieceHeight; row++)
    {
        for (int col = 0; col < pieceWidth; col++)
        {
            switch (num) {
            case 0:
                // code block
                arr[row][col] = piece0[row][col];
                break;
            case 1:
                // code block
                arr[row][col] = piece1[row][col];
                break;
            case 2:
                // code block
                arr[row][col] = piece2[row][col];
                break;
            case 3:
                // code block
                arr[row][col] = piece3[row][col];
                break;
            case 4:
                // code block
                arr[row][col] = piece4[row][col];
                break;
            case 5:
                // code block
                arr[row][col] = piece5[row][col];
                break;
            case 6:
                // code block
                arr[row][col] = piece6[row][col];
                break;
            default:
                // code block
                arr[row][col] = piece0[row][col];
            }
        }
    }
}