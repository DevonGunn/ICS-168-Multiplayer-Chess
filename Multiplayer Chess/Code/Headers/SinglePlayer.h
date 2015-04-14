#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "GeneralizedInclude.h"
#include "MenuButton.h"
#include "Gamestate.h"
#include "ChessPlayer.h"
#include <iostream>

class SinglePlayer :
	public GameState
{
public:
	SinglePlayer(int prevState = NULL);

	//Handles overworld events
	void handleEvents();

	//Processes overworld logic
	void logic();

	//Renders overworld
	void render();

	~SinglePlayer(void);
private:
	//primitives
	int levelWidth, levelHeight;
	bool paused;
	
	//Non-Dynamic Objects
	SDL_Rect chessboardSize;
	SDL_Rect backgroundSize;

	//Dynamic Objects
	SDL_Surface *tileSheet;
	SDL_Surface *screen;

	//Menu Buttons
	MenuButton *title;
	MenuButton *exit;

	//background texture
	SDL_Texture *backgroundTexture;
	//chessboard texture
	SDL_Texture *chessBoard;

	//make our two players
	ChessPlayer player1;
	ChessPlayer player2;
};

#endif