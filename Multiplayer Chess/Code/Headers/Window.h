#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window
{
public:
	Window(int width, int height, SDL_Window *&mainScreen);

	//handle resizing, etc
	void handleEvents(SDL_Window* &mainScreen, SDL_Event *e);

	//toggle fullscreen
	void toggleFullscreen(SDL_Window* &mainScreen);

	//return true if error
	bool error();

	~Window(void);
private:
	//string caption, icon;
	bool windowed, windowOK;
};

#endif