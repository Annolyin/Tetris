
#include "raylib.h"
#include <iostream>

//pieces
const int pieceWidth = 5;
const int pieceHeight = 5;

int piece[pieceHeight][pieceWidth] =
{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
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

const int bCols = 10;
const int bRows = 30;

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


    std::cout << "initialising window \n";
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
            //MoveDown();
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            std::cout << "Input Detected: Left \n";
            if (CheckMoveLeft())
            {
                //RemovePiece(piecePosX, piecePosY);
                //piecePosX--;
                //AddPieceToBoard(piecePosX, piecePosY);
                //DrawBoard();
            }
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
            piecePosX = 5;
            piecePosY = -3;
            std::cout << "No Piece found, adding piece at: " << piecePosX << ", " << piecePosY << "\n";
            AddPieceToBoard(piecePosX, piecePosY);
            DrawBoard();
        }

        //MoveLeft();
        MoveDown();
        //print piece pos
        //std::cout << "Piece Pos: " << piecePosX << ", " << piecePosY << "\n";
        DrawBoard();

        EndDrawing();
        //----------------------------------------------------------------------------------
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
    bool canMove = false;

    //if piece is more than half off the screen
    /*if (piecePosX < (0 - pieceWidth/2))
    {
        return false;
    }*/

    //for each col move down the rows and check for piece
    //when you find the edge of the peice, if it is not at the edge of the board then move it

    //Find the left edge


    //for each col
    for (int c = 0; c < pieceWidth && !canMove < 0; c++)
    {
        //for each row
        for (int r = 0; r < pieceHeight; r++)
        {
            //if piece found
            if (piece[r][c] != 0)
            {
                //if piece is on board
                if (piecePosX + c > 0)
                {
                    //check if there is space to the left on the board
                    if (board[piecePosY + r][piecePosX + c - 1] == 0)
                    {
                        canMove = true;
                    }
                    else
                    {
                        canMove = false;
                    }

                }
            }
        }
    }




    return canMove;
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
    if (CheckMoveDown())
    {
        RemovePiece(piecePosX, piecePosY);

        //DrawBoard();

        piecePosY++;

        AddPieceToBoard(piecePosX, piecePosY);

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
    if (CheckMoveLeft())
    {
        RemovePiece(piecePosX, piecePosY);

        //DrawBoard();

        piecePosX++;

        AddPieceToBoard(piecePosX, piecePosY);

        //DrawBoard();
    }
    else
    {
        piecePosX = -1;
        piecePosY = -1;
    }
}