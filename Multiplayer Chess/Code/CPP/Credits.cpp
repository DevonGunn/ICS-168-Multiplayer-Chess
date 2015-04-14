#include "Credits.h"


Credits::Credits(void)
{
	SDL_Surface *background = loadImage("Resources/Graphics/Backgrounds/Credits.png");

	if (background == NULL)
		cerr << "STATE_CREDITS: Could not load background image.";
	else
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}
	
	//Exit button is our anchor point
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	back = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Back", STATE_TITLE);
}

void Credits::handleEvents()
{
	if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			setNextState(STATE_EXIT);
	
	back->handleEvents();
	exit->handleEvents();
}

void Credits::logic()
{
}

void Credits::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	back->render();
	exit->render();
}

Credits::~Credits(void)
{
	SDL_DestroyTexture(backgroundTexture);

	delete back;
	delete exit;

	back = NULL;
	exit = NULL;
}