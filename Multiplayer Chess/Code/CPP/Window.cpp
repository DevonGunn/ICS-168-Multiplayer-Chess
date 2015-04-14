#include "Window.h"


Window::Window(int width, int height, SDL_Window *&mainScreen)
{
	//create screen at default width/height, default resizeable
	mainScreen = SDL_CreateWindow("Devon Gunn - Multiplayer Chess - Alpha Build",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//errorcheck, finish init if no error
	if (mainScreen == NULL)
	{
		windowOK = false;
	}
	else
	{
		windowOK = true;
		windowed = true;
	}
}

void Window::handleEvents(SDL_Window* &mainScreen, SDL_Event *e)
{
	//make sure window is ok
	if (windowOK)
	{
		if (e->type = SDL_WINDOWEVENT_RESIZED)
		{
			//SDL_SetWindowSize(mainScreen, e->window.data1, e->window.data2);

			if (mainScreen == NULL) windowOK = false;
		}
	}
}

void Window::toggleFullscreen(SDL_Window* &mainScreen)
{
	//first check if window is windowed
	if (windowed)
	{
		//set us to full screen
		SDL_SetWindowFullscreen(mainScreen, SDL_WINDOW_FULLSCREEN_DESKTOP);

		if (mainScreen == NULL)
		{
			windowOK = false;
		}
		else
		{
			windowed = false;
		}
	}
	//otherwise window is already fullscreen
	else
	{
		//revert to windowed mode
		SDL_SetWindowFullscreen(mainScreen, 0);

		if (mainScreen == NULL)
		{
			windowOK = false;
		}
		else
		{
			windowed = true;
		}
	}
}

bool Window::error()
{
	return !windowOK;
}

Window::~Window(void)
{
}
