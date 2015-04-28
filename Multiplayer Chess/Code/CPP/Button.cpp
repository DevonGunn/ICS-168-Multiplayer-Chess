#include "Button.h"


Button::Button(void)
{
}

Button::Button(int xPosition, int yPosition, string text)
{
	//The sprite sheet surface from which we clip the button images
	SDL_Surface *buttonSpriteSheet;

	//Load the button's sprite sheet
	buttonSpriteSheet = loadImage("Resources/Graphics/UI/GUIButtons.png");

	//Error check
	//if (buttonSpriteSheet == NULL) cerr << "Could not load Button's sprite sheet." << endl;

	//The temp surface for our button text
	SDL_Surface *buttonSurfaceText;

	//Create the button's text surface
	buttonSurfaceText = TTF_RenderText_Solid(font, text.c_str(), textColor);

	//Error check
	//if (buttonSurfaceText == NULL) cerr << "Could not create Button's button-text." << endl;

	//read in the buttons x and y position, and size
	//I set width and height first because I use them to calculate x and y
	button.w = buttonSpriteSheet->w / 2;
	button.h = buttonSpriteSheet->h / 2;
	button.x = xPosition - button.w / 2;
	button.y = yPosition - button.h / 2;

	//create some int pointers to hold screen dimensions before falling out of scope
	int *screenW = new int, *screenH = new int;
	SDL_GetWindowSize(mainWindow, screenW, screenH);

	//make sure button isn't going off the screen and fix it if so
	//this allows for up to 0 to button->w/h / 2 wiggle room in button
	//assignment in relation to the edges and corners of the screen
	if (button.x < 0)
		button.x = 0;
	if (button.y < 0)
		button.y = 0;
	if (button.x + button.w > *screenW)
		button.x = *screenW - button.w;
	if (button.y + button.h > *screenH)
		button.y = *screenH - button.h;

	//tell button that button isn't moused over
	mouseOver = false;

	//tell button that it isn't clicked
	clicked = false;

	//Set the clips for our button states
	clips[CLIP_MOUSEOUT].x = 0;
	clips[CLIP_MOUSEOUT].y = 0;
	clips[CLIP_MOUSEOUT].w = button.w;
	clips[CLIP_MOUSEOUT].h = button.h;

	clips[CLIP_MOUSEOVER].x = button.w;
	clips[CLIP_MOUSEOVER].y = 0;
	clips[CLIP_MOUSEOVER].w = button.w;
	clips[CLIP_MOUSEOVER].h = button.h;

	clips[CLIP_MOUSEDOWN].x = 0;
	clips[CLIP_MOUSEDOWN].y = button.h;
	clips[CLIP_MOUSEDOWN].w = button.w;
	clips[CLIP_MOUSEDOWN].h = button.h;

	clips[CLIP_MOUSEUP].x = button.w;
	clips[CLIP_MOUSEUP].y = button.h;
	clips[CLIP_MOUSEUP].w = button.w;
	clips[CLIP_MOUSEUP].h = button.h;

	//Set a default clip state
	clip = clips[CLIP_MOUSEOUT];

	//load the button's sounds
	buttonHover = Mix_LoadWAV("Resources/Audio/SFX/buttonHover.wav");
	buttonSelect = Mix_LoadWAV("Resources/Audio/SFX/buttonSelect.wav");

	//Apply the button text to our button
	applySurface((clip.x + (clip.w / 2)) - (buttonSurfaceText->w / 2), (clip.y + (clip.h / 2)) - (buttonSurfaceText->h / 2), buttonSurfaceText, buttonSpriteSheet);
	applySurface((clip.w + (clip.w / 2)) - (buttonSurfaceText->w / 2), (clip.y + (clip.h / 2)) - (buttonSurfaceText->h / 2), buttonSurfaceText, buttonSpriteSheet);
	applySurface((clip.x + (clip.w / 2)) - (buttonSurfaceText->w / 2), (clip.h + (clip.h / 2)) - (buttonSurfaceText->h / 2), buttonSurfaceText, buttonSpriteSheet);
	applySurface((clip.w + (clip.w / 2)) - (buttonSurfaceText->w / 2), (clip.h + (clip.h / 2)) - (buttonSurfaceText->h / 2), buttonSurfaceText, buttonSpriteSheet);

	//we built the button surface, now store it as a texture
	buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSpriteSheet);

	//Free Surfaces
	SDL_FreeSurface(buttonSpriteSheet);
	SDL_FreeSurface(buttonSurfaceText);
}

void Button::handleEvents()
{
	//create ints to hold mouse coords, replace this with the more efficient method later
	int x = 0, y = 0;

	//controls mouse over
	if (event.type == SDL_MOUSEMOTION)
	{
		//set x and y
		x = event.motion.x;
		y = event.motion.y;

		//if mouse is over button
		if (x > button.x && x < button.x + button.w && y > button.y && y < button.y + button.h)
		{
			//ensure we only play the sound once per mouse hover
			if (!mouseOver)
			{
				//play mouseover sound
				if (buttonHover != NULL)
					Mix_PlayChannel(-1, buttonHover, 0);
			}

			//tell button the cursor is hovering on it
			mouseOver = true;

			//make sure clip only changes if we aren't holding click
			if (!clicked) clip = clips[CLIP_MOUSEOVER];
		}
		//else set clip to mouse out
		else
		{
			//tell button cursor is no longer hovering over it
			mouseOver = false;

			//if the mouse is not currently clicked, change to mouse-out clip
			if (!clicked) clip = clips[CLIP_MOUSEOUT];
		}
	}

	//if mouse is clicked while button is hovered on
	if (event.type == SDL_MOUSEBUTTONDOWN && mouseOver)
	{
		//tell button it has been clicked
		clicked = true;
		//change to clicked clip
		clip = clips[CLIP_MOUSEDOWN];
	} 
	//if mouse button is released
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		//if the cursor was still hovering over button
		if (mouseOver)
		{
			//change clip to mouse-up
			clip = clips[CLIP_MOUSEUP];

			//play confirmation sound!
			if (buttonSelect != NULL)
				Mix_PlayChannel(-1, buttonSelect, 0);
		}
		else
		{
			//immediate change clip since cursor cannot be hovering on button
			clip = clips[CLIP_MOUSEOUT];
		}

		//button released
		clicked = false;
	}
}

void Button::render()
{
	SDL_RenderCopy(renderer, buttonTexture, &clip, &button); //Might need to change the destination rect
}

int Button::width()
{
	return button.w;
}

int Button::height()
{
	return button.h;
}

int Button::getXPos()
{
	return button.x + (button.w / 2);
}

int Button::getYPos()
{
	return button.y + (button.h / 2);
}

bool Button::isClicked()
{
	return clicked;
}

Button::~Button(void)
{
	//destroy textures
	SDL_DestroyTexture(buttonTexture);
	SDL_DestroyTexture(buttonSpriteSheet);

	//free SFX
	Mix_FreeChunk(buttonHover);
	Mix_FreeChunk(buttonSelect);
}
