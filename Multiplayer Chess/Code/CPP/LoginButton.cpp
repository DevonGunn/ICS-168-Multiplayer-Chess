#include "LoginButton.h"


LoginButton::LoginButton()
{
}

LoginButton::LoginButton(int xPosition, int yPosition, string text)
	: Button(xPosition, yPosition, text)
{
}

void LoginButton::handleEvents()
{
	//call parent handleEvents function for base functionality
	Button::handleEvents();

	//loginButton specific code goes here

}

LoginButton::~LoginButton()
{
}
