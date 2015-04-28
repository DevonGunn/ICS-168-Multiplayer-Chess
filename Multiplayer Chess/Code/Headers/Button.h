#ifndef BUTTON_H
#define BUTTON_H

#include "GeneralizedInclude.h"

//using namespace std;

class Button
{
public:
	//default constructor
	Button();

	Button(int xPosition, int yPosition, string text);

	virtual void handleEvents();

	void render();

	int width();

	int height();

	int getXPos();

	int getYPos();

	bool isClicked();

	~Button(void);
protected:
	const enum mouseStates {CLIP_MOUSEOUT, CLIP_MOUSEOVER, CLIP_MOUSEDOWN, CLIP_MOUSEUP};	//Our enumerated type
	
	SDL_Rect button; //Our rect to hold the coordinates and dimensions of our button. We use logically centered coords.
	SDL_Rect clips[4]; //Array of rects to hold the dimensions of each clip from the sprit sheet
	SDL_Rect clip; //Holds the location and size of the clip to show from sprite sheet - may not need
		
	bool mouseOver; //Whether we are moused over the button
	bool clicked; //Whether the mouse is clicked

	Mix_Chunk *buttonHover; //Hover SFX
	Mix_Chunk *buttonSelect; //Click SFX

	SDL_Texture *buttonSpriteSheet; //The sprite sheet surface from which we clip the button images
	SDL_Texture *buttonTexture; //The final texture which we will blit each loop
};

#endif