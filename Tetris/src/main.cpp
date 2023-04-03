
#include "raylib.h"
#include <iostream>

//pieces
const int pieceWidth = 5;
const int pieceHeight = 5;

int piece[pieceHeight][pieceWidth] =
{
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

int piecePosX = -1;
int piecePosY = -1;

void AddPieceToBoard(int xPos, int yPos);
void RemovePiece(int xPos, int yPos);
void DrawBoard();
void MoveDown();
void MoveLeft();
void CheckFullRow();
bool CheckMoveDown();
bool CheckMoveRight();
bool CheckMoveLeft();

//board

const int bCols = 20;
const int bRows = 50;

int tileWidth = 20;
int tileHeight = 20;

int windowWidth = bCols * tileWidth;
int windowHeight = bRows * tileHeight;

char board[bRows][bCols];


void main()
{
    //TestPieces();
    // Initialization
    //--------------------------------------------------------------------------------------


    //initialise board array
    std::cout << "initialise array \n";
    for (int r = 0; r < bRows; r++)
    {
        for (int c = 0; c < bCols; c++)
        {
            board[r][c] = 0;
        }
    }


    std::cout << "initialising window with" << windowWidth<< "x" <<windowHeight << "\n";
    InitWindow(windowWidth, windowHeight, "Tetris");

    SetTargetFPS(1);

    BeginDrawing();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        //read input
        if (IsKeyPressed(KEY_DOWN))
        {
            std::cout << "Input Detected: Down \n";
            MoveDown();
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            std::cout << "Input Detected: Left \n";
            MoveLeft();
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            std::cout << "Input Detected: Right \n";
            if (CheckMoveRight())
            {
                //RemovePiece(piecePosX, piecePosY);
                //piecePosX++;
                //AddPieceToBoard(piecePosX, piecePosY);
                //DrawBoard();
            }
        }

        //if no piece add piece
        if (piecePosX == -1 && piecePosY == -1)
        {
            piecePosX = bCols / 2;
            piecePosY = 0 - (pieceHeight / 2);
            std::cout << "No Piece found, adding piece at: " << piecePosX << ", " << piecePosY << "\n";
            AddPieceToBoard(piecePosX, piecePosY);
            DrawBoard();
        }
        DrawBoard();
        EndDrawing();
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
    std::cout << "Piece Added At: " << piecePosX << ", " << piecePosY << "\n";
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
    piecePosX = -1;
    piecePosY = -1;
}

void DrawBoard()
{
    //draw board
    std::cout << "drawing board \n";
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

void CheckFullRow()
{
    std::cout << "Checking for full row \n";
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
                std::cout << "Full row on row: " << r << "\n";
                fRow = r;
            }

        }
    }
    //clear out the row
    if (fRow >= 0)
    {
        for (int c = 0; c < bCols; c++)
        {
            board[fRow][c] = 0;
        }
    }
}

bool CheckMoveDown()
{
    bool canMove = true;

    if (piecePosY > (bRows - pieceHeight))
    {
        return false;
    }

    //for each index of peice
    for (int r = 0; r < pieceHeight; r++)
    {
        for (int c = 0; c < pieceWidth; c++)
        {
            //if bottom of piece
            if (piece[r][c] != 0 && piece[r + 1][c] == 0)
            {
                //check space on board underneath
                if (board[piecePosY + r + 1][piecePosX + c] != 0)
                {
                    canMove = false;
                }
            }
        }
    }
    return canMove;
}

bool CheckMoveLeft()
{
    bool isSpace = true;

    std::cout << "Checking CanMoveLeft with piece pos: " << piecePosX << "," << piecePosY << "\n";

    //if more than half off board
    if (piecePosX < (0 - (pieceWidth / 2)))
    {
        return false;
    }

    //for each col move down the rows and check for piece
    //when you find the edge of the peice, if it is not at the edge of the board then move it

    //for each col
    for (int c = 0; c < pieceWidth && isSpace; c++)
    {
        //for each row
        for (int r = 0; r < pieceHeight; r++)
        {
            //if piece found
            if (piece[r][c] != 0)
            {
                //check if edge
                if (c == 0 || piece[r][c - 1] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + c - 1][piecePosX + r] != 0)
                    {
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
    bool canMove = true;

    if (piecePosY > (bRows - pieceHeight))
    {
        return false;
    }

    //for each index of peice
    for (int r = 0; r < pieceHeight; r++)
    {
        for (int c = 0; c < pieceWidth; c++)
        {
            //if bottom of piece
            if (piece[r][c] != 0 && piece[r + 1][c] == 0)
            {
                //check space on board underneath
                if (board[piecePosY + r + 1][piecePosX + c] != 0)
                {
                    canMove = false;
                }
            }
        }
    }
    return canMove;
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
        piecePosX = -1;
        piecePosY = -1;
    }
}

void MoveLeft()
{
    int xPos = piecePosX;
    int yPos = piecePosY;
    if (CheckMoveLeft())
    {
        
        RemovePiece(piecePosX, piecePosY);

        //DrawBoard();

        xPos--;

        AddPieceToBoard(xPos, yPos);

        //DrawBoard();
    }
    else
    {
        RemovePiece(piecePosX, piecePosY);
    }
}