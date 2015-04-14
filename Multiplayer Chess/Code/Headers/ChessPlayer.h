#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include "GeneralizedInclude.h"
#include "ChessPiece.h"
#include <vector>

class ChessPlayer
{
public:
	ChessPlayer();

	void handleEvents();

	void render();

	~ChessPlayer();
private:
	static int playerNum;
	std::vector<ChessPiece*> pieces;
};

#endif