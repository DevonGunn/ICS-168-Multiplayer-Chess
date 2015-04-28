#include "MenuButton.h"


MenuButton::MenuButton(void)
{
}

MenuButton::MenuButton(int xPosition, int yPosition, string text, GameStates state)
	: Button(xPosition, yPosition, text)
{
	//store the target state
	targetState = state;
}

void MenuButton::handleEvents()
{
	//call the handle events function of parent
	Button::handleEvents();

	//if the button has been clicked, run our child-class specific code
	if (clicked) setNextState(targetState);
}

//parent destructor is called by default
MenuButton::~MenuButton(void)
{
}
