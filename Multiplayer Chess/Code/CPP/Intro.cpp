#include "Intro.h"


Intro::Intro(void)
{
	//Load our image as a surface
	SDL_Surface *imageSurface = loadImage("Resources/Graphics/Backgrounds/Intro.png");
	
	//Convert our surface to a texture
	background = SDL_CreateTextureFromSurface(renderer, imageSurface);
	
	//Free our surface
	SDL_FreeSurface(imageSurface);

	if (background == NULL) cerr << "STATE_INTRO: Unable to load background image.";

	sfx = Mix_LoadWAV("Resources/Audio/SFX/Intro.wav");

	if (sfx == NULL)
		cerr << "Could not load Intro SFX";

	Mix_PlayChannel(-1, sfx, 0);

	fadeIn.start();
}

void Intro::handleEvents()
{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			setNextState(STATE_EXIT);
		else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
			setNextState(STATE_TITLE);
}

void Intro::logic()
{
	if (fadeIn.getTicks() > 8000)
		setNextState(STATE_TITLE);
}

void Intro::render()
{
	if (fadeIn.getTicks() < 3000)
		SDL_SetTextureAlphaMod(background, 0);
	else if (fadeIn.getTicks() >= 3000 && fadeIn.getTicks() <= 6000)
	{
		SDL_SetTextureAlphaMod(background, ((fadeIn.getTicks() - 3000) / 3000.0) * 255);
	}
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

Intro::~Intro(void)
{
	//Free memory
	SDL_DestroyTexture(background);
	Mix_FreeChunk(sfx);
}
