#include "Camera.h"


Camera::Camera(void)
{
}

Camera::Camera(int x, int y, int cameraWidth, int cameraHeight, int lvlWidth, int lvlHeight)
{
	gameCamera = new SDL_Rect;
	gameCamera->x = x;
	gameCamera->y = y;

	if (cameraWidth != NULL && cameraHeight != NULL)
	{
		gameCamera->w = cameraWidth;
		gameCamera->h = cameraHeight;
	}
	else
	{
		SDL_GetWindowSize(mainWindow, winSizeCaptureW, winSizeCaptureH);
		gameCamera->w = *winSizeCaptureW;
		gameCamera->h = *winSizeCaptureH;
	}

	levelWidth = lvlWidth;
	levelHeight = lvlHeight;
}

void Camera::updateCamera(int x, int y)
{
	//centers camera on provided x/y coords
	gameCamera->x = x - gameCamera->w / 2;
	gameCamera->y = y - gameCamera->h /2;

	//keep camera in bounds
	if (levelWidth != 0 && levelHeight != 0)
	{
		if (gameCamera->x < 0) gameCamera->x = 0;
		if (gameCamera->y < 0) gameCamera->y = 0;
		if (gameCamera->x > levelWidth - gameCamera->w)
			gameCamera->x = levelWidth - gameCamera->w;
		if (gameCamera->y > levelHeight - gameCamera->h)
			gameCamera->y = levelHeight - gameCamera->h;
	}
}

void Camera::updateCamera(const SDL_Rect* object)
{
	//centers camera on provided x/y coords
	gameCamera->x = (object->x + (object->w / 2)) - (gameCamera->w / 2);
	gameCamera->y = (object->y + (object->h / 2)) - (gameCamera->h /2);

	//keep camera in bounds
	if (levelWidth != 0 && levelHeight != 0)
	{
		if (gameCamera->x < 0) gameCamera->x = 0;
		if (gameCamera->y < 0) gameCamera->y = 0;
		if (gameCamera->x > levelWidth - gameCamera->w)
			gameCamera->x = levelWidth - gameCamera->w;
		if (gameCamera->y > levelHeight - gameCamera->h)
			gameCamera->y = levelHeight - gameCamera->h;
	}
}

void Camera::scaleCamera(int width, int height)
{
	gameCamera->w = width;
	gameCamera->h = height;
}

SDL_Rect* &Camera::location()
{
	return *&gameCamera;
}

Camera::~Camera(void)
{
	//delete pointers
	delete gameCamera;
	delete winSizeCaptureW;
	delete winSizeCaptureH;

	//null pointers
	gameCamera = NULL;
	winSizeCaptureW = NULL;
	winSizeCaptureH = NULL;
}
