#include "Options.h"

Options::Options(void)
{
	SDL_Surface *background = loadImage("Resources/Graphics/Backgrounds/Options.png");
	
	if (background == NULL)
		cerr << "STATE_OPTIONS: Could not load background image.";
	else
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}

	//I've decided to make exit the anchor point and build 'up' from it since it remains constant in the menus
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	back = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Back", STATE_TITLE);
}

void Options::handleEvents()
{
	if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		setNextState(STATE_EXIT);

	back->handleEvents();
	exit->handleEvents();
}

void Options::logic()
{
}

void Options::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	back->render();
	exit->render();
}

Options::~Options(void)
{
	SDL_DestroyTexture(backgroundTexture);

	delete back;
	delete exit;

	back = NULL;
	exit = NULL;
}