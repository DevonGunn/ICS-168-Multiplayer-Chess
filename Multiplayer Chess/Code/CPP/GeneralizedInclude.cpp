#include "GeneralizedInclude.h"

//BEGIN GLOBALS//
//Create an SDL Window
SDL_Window* mainWindow = NULL;

//Create window
//Window *mainWindow = NULL;

//Create renderer o3o;
SDL_Renderer *renderer = NULL;

//The event structure o.O <- XD I used to not understand this
SDL_Event event;

//The font - change this font
TTF_Font *font = NULL;

//Initialize the color for the font
SDL_Color textColor = {16, 28, 84};

//Initialize the camera
//Camera is now per-state
//SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//Define state variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

//Create our game timer
Timer time;

//Define showFPS
bool showFPS = true;

//Define State Pointer
GameState *currentState = NULL;

//Set music to null
Mix_Music *music = NULL;
//END GLOBALS//

//BEGIN FUNCTIONS//
bool init()
{
	//Initialize and error check SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	//create screen
	//mainWindow = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, screen);
	mainWindow = SDL_CreateWindow("Devon Gunn - Multiplayer Chess - Alpha Build",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, /*SDL_WINDOW_RESIZABLE | */SDL_WINDOW_OPENGL);
	//error check screen
	if (mainWindow == NULL)
		return false;

	//create renderer for our main window. Hardware Acceleration and VSync enabled.
	renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//set default draw color
	if (renderer != NULL)
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Set logical size of our 'window' for the renderer
	if (SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT) != 0)
		return false;

	//Initialize and error check SDL_ttf
	if (TTF_Init() == -1)
		return false;

	//Initialize and error check SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		return false;
	Mix_Volume(-1, 10);
	Mix_VolumeMusic(10);

	return true;
}

bool loadFiles()
{
	font = TTF_OpenFont("Resources/Misc/ExocetThick.ttf", 28);
	if (font == NULL)
		return 1;
	
	return true;
}

bool isCollision(SDL_Rect a, SDL_Rect b)
{
	int topA = a.y, botA = a.y + a.h,
		leftA = a.x, rightA = a.x + a.w,
		topB = b.y, botB = b.y + b.h,
		leftB = b.x, rightB = b.x + b.w;

	if (topA >= botB)
		return false;
	if (botA <= topB)
		return false;
	if (leftA >= rightB)
		return false;
	if (rightA <= leftB)
		return false;

	return true;
}

SDL_Surface* loadImage(std::string fileName)
{
	//Create surfaces
	SDL_Surface* loadedImage = NULL;
	//SDL_Surface* optimizedImage = NULL;

	//Load temp image
	loadedImage = IMG_Load(fileName.c_str());

	//If temp load sucessful->Optimize
	if (loadedImage != NULL)
	{
		SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0xFF));
		//SDL_CreateTextureFromSurface(renderer, loadedImage);
		//SDL_FreeSurface(loadedImage);
		return loadedImage;
	}
	else
	{
		printf("Unable to load image %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
		return NULL;
	}
	//Make sure image is optimized
	/*if (imageTexture != NULL)
	{
		return imageTexture;
	}
	else printf("Unable to convert image %s to texture! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
	*/
}

Mix_Music* loadMusic(std::string fileName)
{
	return Mix_LoadMUS(fileName.c_str());
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

void setNextState(int newState)
{
	//Make sure user isn't trying to quit before loading next state
	//if (newState != STATE_EXIT)
	//{
		nextState = newState;
	//}
}

void cleanUp()
{
	//Free memory
	delete currentState;
	currentState = NULL;

	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);

	//Close libraries
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}