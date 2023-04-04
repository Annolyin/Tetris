#pragma once
#include <iostream>
#include <fstream>

const int sCols = 5;
const int sRows = 5;
const int sVariants = 4;
enum Rotation { up, right, down, left };

struct Piece {
	int id;
	Rotation rotation;
	int piece[sVariants][sRows][sCols];
};
void SetPiece(Piece p, int* temp);
void RotateLeft(Piece p);
void RotateRight(Piece p);


