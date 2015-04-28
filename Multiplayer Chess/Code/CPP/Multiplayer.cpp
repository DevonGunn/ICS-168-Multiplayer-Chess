#include "Multiplayer.h"


Multiplayer::Multiplayer()
{
	SDL_Surface *background = loadImage("Resources/Graphics/Backgrounds/Credits.png");

	if (background == NULL)
		cerr << "STATE_CREDITS: Could not load background image.";
	else
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}

	//Exit button is our anchor point
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	back = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Back", STATE_TITLE);
	login = new LoginButton(back->getXPos(), back->getYPos() - back->height(), "Login");

	client = new Client();
}

void Multiplayer::handleEvents()
{
	if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		setNextState(STATE_EXIT);

	back->handleEvents();
	exit->handleEvents();
	login->handleEvents();
	if (login->isClicked())
	{
		if(client->connectToServer("127.0.0.1", "27015")) client->sendBuffer("#login#Devon#Bethesda#!");
	}
}

void Multiplayer::logic()
{
}

void Multiplayer::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	login->render();
	back->render();
	exit->render();
}

Multiplayer::~Multiplayer()
{
	SDL_DestroyTexture(backgroundTexture);

	delete back;
	delete exit;
	delete login;
	delete client;

	back = NULL;
	exit = NULL;
	login = NULL;
	client = NULL;
}
