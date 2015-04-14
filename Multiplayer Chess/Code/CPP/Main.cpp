/**
Devon Gunn
#28502436

"Radix" 2-D game engine. All code <C> Devon Gunn.
Please do not use, modify, or distribute without my permission.
I can be reached at "DGunn@CredoIncorporated.com"
**/

//Includes
#include "Credits.h"
#include "GeneralizedInclude.h"
#include "Intro.h"
#include "Options.h"
#include "SinglePlayer.h"
#include "Title.h"
#include <sstream>
#include <string>

//got rid of the namespace to avoid future extensibility issues

int main (int argc, char* args[])
{
	//Initialize program
	if (init() == false)
		return 1;
	if (loadFiles() == false)
		return 1;

	//Set intro to active state and load intro state
	stateID = STATE_INTRO;
	currentState = new Intro();

	//Create our FPS timer
	Timer fps;

	int frame = 0;

	//Create our FPS surfaces
	SDL_Surface* fpsText = NULL;

	//Begin the game timer
	time.start();

	//Create our FPS string stream
	stringstream fpsStream;

	//Create our texture pointer for the text render
	SDL_Texture *fpsRenderedText = NULL;

	//create a rect to hold the position of our fps counter
	SDL_Rect fpsPos;

	//the game loop!
	while (stateID != STATE_EXIT)
	{
		//Start the timer
		fps.start();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
			showFPS = showFPS ? false : true;
			else currentState->handleEvents();
		}

		//Perform current logic
		currentState->logic();

		//Potentially change states
		changeState();

		//create a blank-slate for the screen to draw on
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

		//Render
		currentState->render(); //convert surfaces into textures, copy textures to renderer
		
		//Monitor and cap frame rate
		if (fps.getTicks() < 1000 / FRAMES_PER_SECOND)
		{
			//delay by the difference between our intended and actual frame speeds
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.getTicks());
		}
		
		//this is where it was

		if (showFPS)
		{
			//calculate and store current FPS
			fpsStream << "FPS: " << 1000 / fps.getTicks() <<
				" Time: " << (time.getTicks() / 60000) % 60 << " Minutes, "
				<< (time.getTicks() / 1000) % 60 << " Seconds";

			//Create FPS text and background
			fpsText = TTF_RenderText_Solid(font, fpsStream.str().c_str(), textColor);

			//Clear the stream
			fpsStream.str(std::string());
			fpsStream.clear();

			//generate texture
			fpsRenderedText = SDL_CreateTextureFromSurface(renderer, fpsText);

			//Free the FPS surface
			SDL_FreeSurface(fpsText);

			//Update our text's location each iteration of the loop	
			fpsPos.x = (SCREEN_WIDTH - fpsText->w) / 2;
			fpsPos.y = 0;
			fpsPos.w = fpsText->w;
			fpsPos.h = fpsText->h;

			//Show FPS text
			SDL_RenderCopy(renderer, fpsRenderedText, NULL, &fpsPos);
			
			//Free the FPS texture
			SDL_DestroyTexture(fpsRenderedText);
		}
		
		//Update screen
		SDL_RenderPresent(renderer);

		//need to make some error checking

		++frame;
	}

	cleanUp();

	return 0;
}

void changeState()
{
	if (nextState != STATE_NULL)
	{
		if (nextState != STATE_EXIT)
		{
			delete currentState;
		}
		switch (nextState)
		{
		case STATE_TITLE:
			currentState = new Title();
			break;

		case STATE_CREDITS:
			currentState = new Credits();
			break;

		case STATE_OPTIONS:
			currentState = new Options();
			break;

		case STATE_SINGLEPLAYER:
			currentState = new SinglePlayer();
			break;
		}

		stateID = nextState;

		nextState = STATE_NULL;
	}
}