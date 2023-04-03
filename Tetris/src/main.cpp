
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
void MoveRight();
void CheckFullRow();
bool CheckMoveDown();
bool CheckMoveRight();
bool CheckMoveLeft();
void RotateRight();
void RotateLeft();

//board

const int bCols = 10;
const int bRows = 20;

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

    SetTargetFPS(5);

    BeginDrawing();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        //read input
        if (IsKeyDown(KEY_DOWN))
        {
            std::cout << "Input Detected: Down \n";
            MoveDown();
        }

        if (IsKeyDown(KEY_LEFT))
        {
            std::cout << "Input Detected: Left \n";
            MoveLeft();
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            std::cout << "Input Detected: Right \n";
            MoveRight();
        }

        if (IsKeyDown(KEY_UP))
        {
            std::cout << "Input Detected: Up \n";
            RotateRight();
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
        CheckFullRow();
        //MoveDown();
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
    std::cout << "Checking CanMoveLeft with piece pos: " << piecePosX << "," << piecePosY << "\n";

    //if more than half off board
    if (piecePosX < (0 - (pieceWidth / 2)))
    {
        std::cout << "piece at edge of board. returning false \n";
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
                    std::cout << "piece at edge of board. returning false \n";
                    return false;
                }
                //check if edge
                if (c == 0 || piece[r][c - 1] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + r][piecePosX + c - 1] != 0)
                    {
                        std::cout << "no space next to piece, returning false \n";
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
    std::cout << "Checking CanMoveRight with piece pos: " << piecePosX << "," << piecePosY << "\n";

    //if more than half off board
    if (piecePosX > (bCols + (pieceWidth / 2)))
    {
        std::cout << "piece at edge of board. returning false \n";
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
                    std::cout << "piece at edge of board. returning false \n";
                    return false;
                }
                //check if edge
                if (c == pieceWidth || piece[r][c + 1] == 0)
                {
                    //if space on board to left
                    if (board[piecePosY + r][piecePosX + c + 1] != 0)
                    {
                        std::cout << "no space next to piece, returning false \n";
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
        std::cout << "moving left \n";
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
        std::cout << "moving right \n";
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
    std::cout << "Rotating piece";
    int pieceSize = pieceHeight;
    for (int r = 0; r < pieceSize; r++) 
    {
        for (int c = 0; c < pieceSize - r; c++)
        {
            int temp = piece[r][c];
            piece[r][c] = piece[pieceSize - 1 - c][pieceSize - 1 - r];
            piece[pieceSize - 1 - c][pieceSize - 1 - r] = temp;
        }
    }
    for (int r = 0; r < pieceSize / 2; r++) {
        for (int c= 0; c < pieceSize; c++) {
            int ptr = piece[r][c];
            piece[r][c] = piece[pieceSize - 1 - r][c];
            piece[pieceSize - 1 - r][c] = ptr;
        }
    }
    AddPieceToBoard(posX, posY);
    DrawBoard();
}

void RotateLeft()
{

}