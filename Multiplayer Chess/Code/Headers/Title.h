#ifndef TITLE_H
#define TITLE_H

#include "GameState.h"
#include "GeneralizedInclude.h"
#include "MenuButton.h"
#include <iostream>

using namespace std;

class Title :
	public GameState
{
public:
	Title(void);

	//Handles intro events
	void handleEvents();

	//Handles intro logic
	void logic();

	//Handles intro rendering
	void render();

	~Title(void);
private:
	MenuButton *singlePlayer;
	MenuButton *options;
	MenuButton *credits;
	MenuButton *exit;

	SDL_Texture *backgroundTexture;
};

#endif