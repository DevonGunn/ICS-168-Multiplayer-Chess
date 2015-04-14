#ifndef BUTTON_H
#define BUTTON_H

#include "GeneralizedInclude.h"

using namespace std;

class Button
{
public:
	//virtual void handleEvents() = 0;

	//virtual void render() = 0;

	//virtual ~Button(void){};
protected:
	const enum mouseStates {CLIP_MOUSEOUT, CLIP_MOUSEOVER, CLIP_MOUSEDOWN, CLIP_MOUSEUP};	//Our enumerated type
	
	SDL_Rect button; //Our rect to hold the coordinates and dimensions of our button. We use logically centered coords.
	SDL_Rect clips[4]; //Array of rects to hold the dimensions of each clip from the sprit sheet
	SDL_Rect clip; //Holds the location and size of the clip to show from sprite sheet - may not need

	GameStates targetState; //The state the button will lead to when clicked
		
	bool mouseOver; //Whether we are moused over the button
	bool clicked; //Whether the mouse is clicked

	Mix_Chunk *buttonHover; //Hover SFX
	Mix_Chunk *buttonSelect; //Click SFX

	SDL_Texture *buttonSpriteSheet; //The sprite sheet surface from which we clip the button images
	SDL_Texture *buttonTexture; //The final texture which we will blit each loop
};

#endif