#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "GameState.h"
#include "GeneralizedInclude.h"
#include "MenuButton.h"
#include "LoginButton.h"
#include "Client.h"
#include <iostream>

class Multiplayer :
	public GameState
{
public:
	Multiplayer(void);

	void handleEvents();

	void logic();

	void render();

	~Multiplayer(void);
private:
	MenuButton *back;
	MenuButton *exit;
	LoginButton *login;

	Client *client;

	SDL_Texture *backgroundTexture;
};
#endif