#include "SinglePlayer.h"

SinglePlayer::SinglePlayer(int prevState)
{
	SDL_Surface *background = loadImage("Resources/Graphics/Backgrounds/chessBackground.png");

	if (background == NULL)
		cerr << "STATE_TITLE: Could not load background image.";
	else
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}

	background = loadImage("Resources/Graphics/Backgrounds/chessBoard.png");

	if (background == NULL)
		cerr << "STATE_TITLE: Could not load background image.";
	else
	{
		chessBoard = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}

	//We are stealing a surface from the main window
	screen = SDL_GetWindowSurface(mainWindow);

	//Exit is our UI Anchor
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	title = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Main Menu", STATE_TITLE);
	
	//If music is already playing, unload it
	if (Mix_PlayingMusic())
	{
		Mix_FreeMusic(music);
	}

	//Load overworld music
	music = loadMusic("Resources/Audio/Music/SinglePlayer.ogg");
	
	//If it loaded correctly, play the music
	if (music != NULL)
	{
		Mix_PlayMusic(music, -1);
	}

	//The game does not start paused :P
	paused = false;

	//set the size of the space for the chessboard and border area of the chessboard
	chessboardSize = { 0, 0, 600, 600 };
	backgroundSize = { 600, 0, 200, 600 };

	//initialize our players
	player1 = ChessPlayer();
	//player2 = ChessPlayer();
}

void SinglePlayer::handleEvents()
{
	//line to handle character movement
	if (event.type == SDL_QUIT)
		setNextState(STATE_EXIT);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		paused = !paused;

	if (paused)
	{
		//should eventually create a data structure to house UI elements and iterate through them with handle events.
		//title UI button
		title->handleEvents();
		//exit UI button
		exit->handleEvents();
	}

	if (!paused)
	{
		//Going to need to iterate through data structure holding all objects which need to cycle events
		
	}
}

void SinglePlayer::logic()
{
	if (!paused)
	{
	}
}

void SinglePlayer::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundSize);
	SDL_RenderCopy(renderer, chessBoard, NULL, &chessboardSize);

	//render player pieces
	player1.render();
	//player2.render();

	if (paused)
	{
		title->render();
		exit->render();
	}
}

SinglePlayer::~SinglePlayer(void)
{
	//Free resources
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(chessBoard);

	//Release our screen surface
	SDL_FreeSurface(screen);
	
	//Delete and Null our buttons
	delete title;
	delete exit;

	title = NULL;
	exit = NULL;

	//Delete and Null our tilesheet
	delete tileSheet;
	tileSheet = NULL;

	//Free and stop music
	Mix_FreeMusic(music);
}