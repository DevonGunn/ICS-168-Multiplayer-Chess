#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include "GeneralizedInclude.h"

class ChessPiece
{
public:
	ChessPiece();
	ChessPiece(PlayerColor pColor);

	void render();

	~ChessPiece();
private:
	//our chess piece sprite sheet
	SDL_Texture *spriteSheet; //need to make it so this is static
	//Sprite sheet clip keeps track of a rect that holds the
	//sprite sheet coordinates to render the right tile.
	//Position holds the piece's position on the board.
	SDL_Rect spriteSheetClip, position;
	//Each board square is 75 x 75 pixels width x height

	//keep track of # of pieces and if the number is incremented 
	//we know to put piece in next known position for that type on board
	static int numBlackPieces;
	static int numWhitePieces;

	//enumerated types for pieces
	const enum PieceName { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
	
	PieceName pieceType;
};

#endif