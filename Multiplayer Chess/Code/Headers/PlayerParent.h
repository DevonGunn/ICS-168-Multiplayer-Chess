#ifndef PLAYERPARENT_H
#define PLAYERPARENT_H

#include "GeneralizedInclude.h"

class PlayerParent
{
public:
	PlayerParent();
	PlayerParent(int xPos, int yPos);
	virtual void handleEvents() = 0;
	virtual void move() = 0;
	virtual void render(SDL_Rect *camLoc) = 0;
	SDL_Rect* location();
	~PlayerParent();
protected:
	//keep track of number of lives across all instances of player
	//static int lives;
	
	//primitives
	int xVelocity, yVelocity, maxVelocity,
		speed, frame, facing, lastKey, currentAnimTime;

	bool moving, audioPlaying;

	const enum facing {DOWN, LEFT, RIGHT, UP};
	
	//Timers; one for frame-based smooth movement, one for animation speed
	Timer movementTimer, animationTimer;

	//This holds the x & y positions of our player
	//And our width and height
	//character holds literal coordinates relative to in game world
	//characterLogicalPosition holds coordinates relative to viewport
	SDL_Rect character, characterLogicalPosition;
	
	//dynamic objects
	//This temporarily holds the sprite sheet; declare and free in constructor
	//SDL_Surface *spriteSheetSurface;
	SDL_Texture *spriteSheet;

	//dynamic array that we create custom sized in our children classes
	//this syntax means we are making a pointer
	//which will hold another pointer
	SDL_Rect **animationClips;
	
	//dynamic array for SFX; it'll be filled with pointers
	Mix_Chunk **sfx;

	//allows us to change our animation array frame #'s automatically
	int animNumRows, animNumColumns, numSFX;
};

#endif