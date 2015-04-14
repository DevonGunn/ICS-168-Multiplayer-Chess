#ifndef OPTIONS_H
#define OPTIONS_H

#include "GameState.h"
#include "GeneralizedInclude.h"
#include "MenuButton.h"
#include <iostream>

class Options :
	public GameState
{
public:
	//Loads options resources
	Options(void);

	//Handles options events
	void handleEvents();

	//Handles options logic
	void logic();

	//Handles options rendering
	void render();

	//Destructor
	~Options(void);

private:
	MenuButton *back;
	MenuButton *exit;

	SDL_Texture *backgroundTexture;
};

#endif