#include "Pieces.h"
#include <iostream>
#include <fstream>


void RotateLeft(Piece p)
{
	switch (p.rotation)
	{
	case up:
		p.rotation = left;
		break;
	case left:
		p.rotation = down;
		break;
	case down:
		p.rotation = right;
		break;
	case right:
		p.rotation = up;
		break;
	default:
		break;
	}
}

void RotateRight(Piece p)
{
	switch (p.rotation)
	{
	case up:
		p.rotation = right;
		break;
	case right:
		p.rotation = down;
		break;
	case down:
		p.rotation = left;
		break;
	case left:
		p.rotation = up;
		break;
	default:
		break;
	}
}

void PrintPiece(Piece p)
{
	int r = 0;
	switch (p.rotation)
	{
	case up:
		r = 0;
		break;
	case right:
		r = 1;
		break;
	case down:
		r = 2;
		break;
	case left:
		r = 3;
		break;
	default:
		break;
	}

	for (int row = 0; row < sRows; row++)
	{
		for (int col = 0; col < sCols; col++)
		{
			std::cout << p.piece[r][row][col] << ", ";
		}
		std::cout << " \n";
	}
}

void SetPiece(Piece p, int* temp)
{
	//p.piece = temp;
	//for (int var = 0; var < sVariants; var++)
	//{
	//	for (int row = 0; row < sRows; row++)
	//	{
	//		for (int col = 0; col < sCols; col++)
	//		{
	//			p.piece[var][row][col] = temp[var][row][col];
	//		}
	//	}
	//}
}