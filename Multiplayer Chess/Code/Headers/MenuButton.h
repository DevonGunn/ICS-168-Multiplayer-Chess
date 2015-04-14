#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "button.h"

using namespace std;

class MenuButton :
	public Button
{
public:
	MenuButton(void);

	//MenuButton - Constructs a menu button at a given position that leads to a target state
	//@param int - the positive or 0 X offset between the logical surface and screen
	//@param int - the positive or 0 Y offset between the logical surface and screen
	//@param string - the text to place on the button
	//@param GameStates - the game-state that the button will take us to when clicked
	MenuButton(int xPosition, int yPosition, string text, GameStates state);

	void handleEvents(/*SDL_Surface* &bGround/*int xPos, int yPos*/);

	void render();

	//width - returns the width of the button
	//@return int - returns the width of the button
	int width();

	int height();

	int getXPos();

	int getYPos();

	~MenuButton(void);
};

#endif