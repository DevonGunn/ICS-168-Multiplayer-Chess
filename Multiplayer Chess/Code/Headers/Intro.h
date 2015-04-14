#ifndef INTRO_H
#define INTRO_H

#include "GameState.h"
#include "GeneralizedInclude.h"
#include <iostream>

class Intro :
	public GameState
{
public:
	//Loads intro resources
	Intro(void);

	//Handles intro events
	void handleEvents();

	//Handles intro logic
	void logic();

	//Handles intro rendering
	void render();

	//Destructor
	~Intro(void);

private:
	SDL_Texture *background;
	Mix_Chunk *sfx;
	Timer fadeIn;

	bool played;
};

#endif