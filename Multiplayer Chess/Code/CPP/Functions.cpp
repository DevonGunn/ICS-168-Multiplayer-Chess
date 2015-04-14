#include "Functions.h"

//
//bool init()
//{
//	//Initialize and error check SDL
//	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
//		return false;
//
//	//Set the Icon
//	SDL_WM_SetIcon(loadImage("GameIcon.ico"), NULL);
//
//	//Initialize screen
//	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
//
//	//Error check screen
//	if (screen == NULL)
//		return false;
//
//	//Initialize and error check SDL_ttf
//	if (TTF_Init() == -1)
//		return false;
//
//	//Initialize and error check SDL_mixer
//	//if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
//		//return false;
//
//	//Set caption for game window
//	SDL_WM_SetCaption("Adventure Game!~", NULL);
//
//	return true;
//}
//
//bool loadFiles()
//{
//	font = TTF_OpenFont("lazy.ttf", 28);
//	if (font == NULL)
//		return 1;
//	
//	return true;
//}
//
//bool collision(SDL_Rect a, SDL_Rect b)
//{
//	int topA = a.y, botA = a.y + a.h,
//		leftA = a.x, rightA = a.x + a.w,
//		topB = b.y, botB = b.y + b.h,
//		leftB = b.x, rightB = b.x + b.w;
//
//	if (topA <= botB)
//		return false;
//	if (botA >= topB)
//		return false;
//	if (leftA >= rightB)
//		return false;
//	if (rightA <= leftB)
//		return false;
//
//	return true;
//}
//
//SDL_Surface* loadImage(std::string fileName)
//{
//	//Create surfaces
//	SDL_Surface* loadedImage = NULL;
//	SDL_Surface* optimizedImage = NULL;
//
//	//Load temp image
//	loadedImage = IMG_Load(fileName.c_str());
//
//	//If temp load sucessful->Optimize
//	if (loadedImage != NULL)
//	{
//		optimizedImage = SDL_DisplayFormat(loadedImage);
//
//		SDL_FreeSurface(loadedImage);
//	}
//
//	//Make sure image is optimized
//	if (optimizedImage != NULL)
//	{
//		//Define and set colorkey in one step
//		SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
//	}
//
//	return optimizedImage;
//}
//
////Mix_Music* loadMusic(std::string fileName)
////{
////	return Mix_LoadMUS(fileName.c_str());
////}
//
//void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
//{
//	SDL_Rect offset;
//
//	offset.x = x;
//	offset.y = y;
//
//	SDL_BlitSurface(source, clip, destination, &offset);
//}
//
//void setNextState(int newState)
//{
//	//Make sure user isn't trying to quit before loading next state
//	//if (newState != STATE_EXIT)
//	//{
//		nextState = newState;
//	//}
//}
//
////void changeState()
////{
////	if (nextState != STATE_NULL)
////	{
////		if (nextState != STATE_EXIT)
////		{
////			delete currentState;
////		}
////		switch (nextState)
////		{
////		case STATE_TITLE:
////			currentState = new Title();
////			break;
////
////		/*case STATE_CREDITS:
////			currentState = new Credits();
////			break;
////
////		case STATE_OPTIONS:
////			currentState = new Options();
////			break;
////
////		case STATE_OVERWORLD:
////			currentState = new OverWorld(stateID);
////			break;*/
////		}
////
////		stateID = nextState;
////
////		nextState = STATE_NULL;
////	}
////}
//
//void cleanUp()
//{
//	//Free memory
//	delete currentState;
//	TTF_CloseFont(font);
//
//	//Close libraries
//	//Mix_CloseAudio();
//	TTF_Quit();
//	SDL_Quit();
//}