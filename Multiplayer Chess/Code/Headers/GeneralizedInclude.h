#ifndef GENERALIZEDINCLUDE_H
#define GENERALIZEDINCLUDE_H

#include "GameState.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Timer.h"
#include "Window.h"
#include <string>


using namespace std;

//CONSTANTS BEGIN//
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRAMES_PER_SECOND = 60;

//Custom enumerated type for the game states
const enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_TITLE,
	STATE_CREDITS,
	STATE_OPTIONS,
	STATE_SINGLEPLAYER,
	STATE_EXIT
};

const enum PlayerColor
{
	BLACK,
	WHITE
};
//CONSTANTS END//

//GLOBALS BEGIN//
//Declare SDL Window
extern SDL_Window* mainWindow;

//Declare window
//extern Window* mainWindow;

//Create renderer
extern SDL_Renderer* renderer;

//Declare the event structure o.O
extern SDL_Event event;

//Declare the font
extern TTF_Font *font;

//Declare the color for the font
extern SDL_Color textColor;

//Declare the camera
//update: camera is now per state
//extern SDL_Rect camera;

//Define state variables
extern int stateID;
extern int nextState;

//Create our game timer
extern Timer time;

//Define State Pointer
extern GameState *currentState;

//Create our FPS/Timer switch
extern bool showFPS;

//Music sound track
extern Mix_Music *music;
//GLOBALS END//

//FUNCTIONS BEGIN//

//init - initializes the SDL and sets up the window
//@return bool - returns true if initialization succeeded; false otherwise
bool init();

//loadFiles - loads the game files
//@return bool - returns true if files loaded; false otherwise
bool loadFiles();

//collision - checks the collision of two provided rects
//@param SDL_Rect - first rect to check for collision with second rect
//@param SDL_Rect - second rect to check for collision with first rect
//@return bool - whether or not first and second rect collide
bool isCollision(SDL_Rect a, SDL_Rect b);

//loadImage - loads an image into the program
//@param string - file name of image to load
//@return SDL_Surface* - pointer to surface object that was loaded
SDL_Surface* loadImage(std::string);

//loadMusic - loads a music file
//@param string - file name of music to load
//@return Mix_Music* - pointer to Mix_Music object
Mix_Music* loadMusic(std::string);

//applySurface - blits a source surface onto destination surface with x y offset
//@param int - x offset
//@param int - y offset
//@param SDL_Surface* - pointer to source surface
//@param SDL_Surface* - pointer to destination surface
//@param SDL_Rect* - pointer to SDL_Rect containing coordinates to clip-blit, default set to NULL
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

//setNextState - sets the next state for finite state engine
//@param int - the next state to set
void setNextState(int newState);

//changeState - changes the state
void changeState();

//cleanUp - frees memory
void cleanUp();
//FUNCTIONS END//
#endif