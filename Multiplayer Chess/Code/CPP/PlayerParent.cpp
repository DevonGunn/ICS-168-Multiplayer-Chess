#include "PlayerParent.h"


PlayerParent::PlayerParent()
{
}

PlayerParent::PlayerParent(int xPos, int yPos)
{
	character.x = xPos;
	character.y = yPos;

	speed = 200;

	xVelocity = yVelocity = 0;

	//lives = 3;

	//start the timers we use to cordinate our player
	movementTimer.start();
	animationTimer.start();

	currentAnimTime = 0;

	//set default animation frame; facing is in child classes
	frame = 0;

	//set last key
	lastKey = NULL;

	//init variables
	moving = false;
	audioPlaying = false;
}

void PlayerParent::render(SDL_Rect *camLoc)
{

}

SDL_Rect* PlayerParent::location()
{
	return &character;
}

PlayerParent::~PlayerParent()
{
	//clean up :D
	SDL_DestroyTexture(spriteSheet);
	
	//delete pointers
	if (animationClips != NULL)
	{
		for (int i = 0; i < animNumRows; ++i)
		{
			delete[] animationClips[i];
		}

		delete[] animationClips;
	}

	if (sfx != NULL)
	{
		for (int i = 0; i < numSFX; ++i)
		{
			Mix_FreeChunk(sfx[i]);
		}

		delete[] sfx;
	}
}
