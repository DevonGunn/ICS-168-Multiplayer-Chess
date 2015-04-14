#include "ChessPiece.h"

//since these are static member variables, we must define them here
int ChessPiece::numBlackPieces = 0;
int ChessPiece::numWhitePieces = 0;

ChessPiece::ChessPiece()
{
}

ChessPiece::ChessPiece(PlayerColor pColor)
{
	//initialize the width/height of our two rects
	spriteSheetClip.w = spriteSheetClip.h = position.w = position.h = 75;

	//I might need to add additional logic to make sure it doesn't try to use more memory than needed

	//load the chess pieces texture onto a surface
	SDL_Surface *spriteImage = loadImage("Resources/Graphics/TileSets/chessSet.png");

	//error check
	if (spriteImage == NULL)
		std::cerr << "STATE_TITLE: Could not load background image.";
	//if no errors then optimize the surface into a texture for rendering and load it into our static shared sprite sheet for all pieces.
	else
	{
		spriteSheet = SDL_CreateTextureFromSurface(renderer, spriteImage);
		SDL_FreeSurface(spriteImage);
	}

	//logic to determine initial piece placement on map
	if (pColor == BLACK)
	{
		//handle x-position since this never changes
		position.x = (numBlackPieces % 8) * 75;

		//case for handling first row of pieces
		if (numBlackPieces < 8)	position.y = 0;
		//case for handling second row of pieces
		else position.y = 75;

		//handle determining what piece this is
		if (numBlackPieces == 0 || numBlackPieces == 7) pieceType = ROOK;
		else if (numBlackPieces == 1 || numBlackPieces == 6) pieceType = KNIGHT;
		else if (numBlackPieces == 2 || numBlackPieces == 5) pieceType = BISHOP;
		else if (numBlackPieces == 3) pieceType = QUEEN;
		else if (numBlackPieces == 4) pieceType = KING;
		else pieceType = PAWN;
	}
	else if (pColor == WHITE)
	{
		position.x = (numWhitePieces % 8) * 75;
		
		if (numWhitePieces < 8)	position.y = 450;
		else position.y = 525;

		if (numWhitePieces < 8) pieceType = PAWN;
		else if (numWhitePieces == 8 || numWhitePieces == 15) pieceType = ROOK;
		else if (numWhitePieces == 9 || numWhitePieces == 14) pieceType = KNIGHT;
		else if (numWhitePieces == 10 || numWhitePieces == 13) pieceType = BISHOP;
		else if (numWhitePieces == 11) pieceType = QUEEN;
		else pieceType = KING;
	}

	//set x and y positions for the clip in the sprite sheet
	spriteSheetClip.x = 100 * pieceType;
	spriteSheetClip.y = (pColor == BLACK) ? 0 : 75;

	//increment piece counter
	if (pColor == BLACK) ++numBlackPieces;
	else if (pColor == WHITE) ++numWhitePieces;

	//mouse over is default set to false
	mouseOver = clicked = false;

	//load the SFX
	pieceSelect = Mix_LoadWAV("Resources/Audio/SFX/pieceSelect.wav");
	pieceRelease = Mix_LoadWAV("Resources/Audio/SFX/pieceRelease.wav");

	//set the initial offset
	xOffset = yOffset = 0;
}

void ChessPiece::handleEvents()
{
	//create ints to hold mouse coords, replace this with the more efficient method later
	int x = 0, y = 0;

	//controls mouse over
	if (event.type == SDL_MOUSEMOTION)
	{
		//set x and y
		x = event.motion.x;
		y = event.motion.y;

		//if mouse is over piece
		if (x > position.x && x < position.x + position.w && y > position.y && y < position.y + position.h)
		{
			//ensure we only play the sound once per mouse hover
			if (!mouseOver)
			{
				//play mouseover sound
				//if (pieceSelect != NULL)
					//Mix_PlayChannel(-1, pieceSelect, 0);
			}

			//tell piece the cursor is hovering on it
			mouseOver = true;

		}
		//else set clip to mouse out
		else
		{
			//tell piece cursor is no longer hovering over it
			mouseOver = false;
		}

		//If the button has been clicked, then drag the piece and stop moving it when the click has been released
		if (clicked)
		{
			position.x = x - xOffset;
			position.y = y - yOffset;
		}

		//set the offset incase we need it
		xOffset = x - position.x;
		yOffset = y - position.y;
	}

	//if mouse is clicked while piece is hovered on
	if (event.type == SDL_MOUSEBUTTONDOWN && mouseOver)
	{
		//play select sound!
		if (pieceSelect != NULL)
			Mix_PlayChannel(-1, pieceSelect, 0);

		//tell piece it has been clicked
		clicked = true;
	}

	//if mouse button is released
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		//if the cursor was still hovering over piece
		if (mouseOver)
		{
			//play confirmation sound!
			if (pieceRelease != NULL)
				Mix_PlayChannel(-1, pieceRelease, 0);

			clicked = false;
		}
		else
		{
			//button released while no mouse-over
			clicked = false;
		}
	}
}

void ChessPiece::render()
{
	SDL_RenderCopy(renderer, spriteSheet, &spriteSheetClip, &position);
}

ChessPiece::~ChessPiece()
{
	//free dynamic memory
	SDL_DestroyTexture(spriteSheet);

	Mix_FreeChunk(pieceSelect);
	Mix_FreeChunk(pieceRelease);
}
