#include "PlayerOverworld.h"


PlayerOverworld::PlayerOverworld()
{
}

PlayerOverworld::PlayerOverworld(int xPos, int yPos,
	int lvlWidth, int lvlHeight)
	: PlayerParent(xPos, yPos)
{
	//temporary piece until ingame collision works
	levelWidth = lvlWidth;
	levelHeight = lvlHeight;

	//create a temp surface to load the sprite sheet into and take dimensions
	SDL_Surface *spriteSheetSurface = loadImage("Resources/Graphics/Characters/player.png");

	//save the dimensions of our character by dividing sheet
	//by number of frames in each direction
	character.w = spriteSheetSurface->w / 4;
	character.h = spriteSheetSurface->h / 4;

	//set the viewport's relative position placement's width and height
	characterLogicalPosition.w = character.w;
	characterLogicalPosition.h = character.h;

	//convert and load the temp surface into texture
	spriteSheet = SDL_CreateTextureFromSurface(renderer, spriteSheetSurface);

	//free the temp surface
	SDL_FreeSurface(spriteSheetSurface);

	//Set the initial facing of our sprite
	facing = DOWN;

	//decide how many frames vertical and horizontal our player has
	//we're going to use Row-Major Ordering
	animNumRows = 4;
	animNumColumns = 4;

	//set number of SFX the character currently has
	numSFX = 1;

	//allocate dynamic array to hold our frame clips
	animationClips = new SDL_Rect*[animNumRows];

	//initialize our dynamic array
	for (int i = 0; i < animNumRows; ++i)
	{
		animationClips[i] = new SDL_Rect[animNumColumns];
	}

	//populate our dynamic array with the frame numbers/sizes
	for (int i = 0; i < animNumRows; ++i)
	{
		for (int j = 0; j < animNumColumns; ++j)
		{
			animationClips[i][j].x = j * character.w;
			animationClips[i][j].y = i * character.h;
			animationClips[i][j].w = character.w;
			animationClips[i][j].h = character.h;
		}

	}

	//Initialize our SFX DArray
	sfx = new Mix_Chunk*[numSFX];

	//fill our SFX DArray
	sfx[footsteps] = Mix_LoadWAV("Resources/Audio/SFX/footsteps.wav");

}

void PlayerOverworld::handleEvents()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (xVelocity != -speed)
			{
				xVelocity = -speed;
				lastKey = LEFT;
			}
			break;
		case SDLK_RIGHT:
			if (xVelocity != speed)
			{
				xVelocity = speed;
				lastKey = RIGHT;
			}
			break;
		case SDLK_UP:
			if (yVelocity != -speed)
			{
				yVelocity = -speed;
				lastKey = UP;
			}
			break;
		case SDLK_DOWN:
			if (yVelocity != speed)
			{
				yVelocity = speed;
				lastKey = DOWN;
			}
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (xVelocity == -speed) xVelocity = 0;
			break;
		case SDLK_RIGHT:
			if (xVelocity == speed) xVelocity = 0;
			break;
		case SDLK_UP:
			if (yVelocity == -speed) yVelocity = 0;
			break;
		case SDLK_DOWN:
			if (yVelocity == speed) yVelocity = 0;
			break;
		default:
			break;
		}
	}
}

void PlayerOverworld::move()
{
	//move the player
	character.x += xVelocity * (movementTimer.getTicks() / 1000.f);
	character.y += yVelocity * (movementTimer.getTicks() / 1000.f);

	//keep the player in bounds
	if (character.x < 0) character.x = 0;
	if (character.y < 0) character.y = 0;
	//level width and height is temporary until have
	//in game objects making impassable borders
	if (character.x > levelWidth - character.w)
		character.x = levelWidth - character.w;
	if (character.y > levelHeight - character.h)
		character.y = levelHeight - character.h;

	//check collision with walls

	movementTimer.start();
}

void PlayerOverworld::render(SDL_Rect *camLoc)
{
	currentAnimTime = animationTimer.getTicks();

	if (xVelocity != 0 && yVelocity != 0)
	{
		moving = true;
		facing = lastKey;

		if (currentAnimTime >= 250)
			++frame;
	}
	else if (xVelocity != 0)
	{
		moving = true;
		facing = xVelocity > 0 ? RIGHT : LEFT;

		if (currentAnimTime >= 250)
			++frame;
	}
	else if (yVelocity != 0)
	{
		moving = true;
		facing = yVelocity > 0 ? DOWN : UP;

		if (currentAnimTime >= 250)
			++frame;
	}
	else
	{
		frame = 0;
		moving = false;
	}

	//reset timer every 1/4th sec
	if (currentAnimTime >= 250)
		animationTimer.start();

	//loop frames
	if (frame >= 4) frame = 0;

	//apply frame clip and draw
	//applySurface(static_cast<int>(xPos - camLoc->x), static_cast<int>(yPos - camLoc->y), spriteSheet, bgSurface, &animation[status][frame]);
	characterLogicalPosition.x = static_cast<int>(character.x - camLoc->x);
	characterLogicalPosition.y = static_cast<int>(character.y - camLoc->y);

	SDL_RenderCopy(renderer, spriteSheet, &animationClips[facing][frame], &characterLogicalPosition);

	if (moving && !audioPlaying)
	{
		Mix_PlayChannel(-1, sfx[footsteps], -1);

		audioPlaying = true;;
	}
	else if (!moving && audioPlaying)
	{
		if (Mix_GetChunk(0) == sfx[footsteps])
			Mix_HaltChannel(0);
		else if (Mix_GetChunk(1) == sfx[footsteps])
			Mix_HaltChannel(1);

		audioPlaying = false;
	}
}

PlayerOverworld::~PlayerOverworld()
{
}
