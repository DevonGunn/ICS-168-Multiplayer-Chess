#include "ChessPlayer.h"

//define static playernumber
int ChessPlayer::playerNum = 1;

ChessPlayer::ChessPlayer()
{
	//determine what color the player is
	PlayerColor tempColor = (playerNum == 1) ? WHITE : BLACK;

	//populate this player's chess pieces
	for (unsigned int i = 0; i < 16; ++i)
	{
		ChessPiece *temp;
		temp = new ChessPiece(tempColor);
		pieces.push_back(temp);
	}

	playerNum++;
}

void ChessPlayer::render()
{
	for (unsigned int i = 0; i < pieces.size(); ++i)
	{
		pieces[i]->render();
	}
}

ChessPlayer::~ChessPlayer()
{
	//clean up memory
	/*for (unsigned int i = 0; i < pieces.size(); ++i)
	{
		delete pieces[i];
		pieces[i] = NULL;
	}*/
}
