#ifndef LOGINBUTTON_H
#define LOGINBUTTON_H

#include "Button.h"

class LoginButton :
	public Button
{
public:
	LoginButton();
	LoginButton(int xPosition, int yPosition, string text);
	
	void handleEvents();

	~LoginButton();
};

#endif