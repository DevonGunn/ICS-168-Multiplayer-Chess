#ifndef CREDITS_H
#define CREDITS_H

#include "GameState.h"
#include "GeneralizedInclude.h"
#include "MenuButton.h"
#include <iostream>

class Credits :
	public GameState
{
public:
	Credits(void);

	void handleEvents();

	void logic();

	void render();

	~Credits(void);
private:
	MenuButton *back;
	MenuButton *exit;
	
	SDL_Texture *backgroundTexture;
};
#endif