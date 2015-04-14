#ifndef CAMERA_H
#define CAMERA_H

#include "GeneralizedInclude.h"

class Camera
{
public:
	//constructor and overloaded constructor
	Camera(void);
	Camera(int x, int y, int cameraWidth = 0, int cameraHeight = 0, int lvlWidth = 0, int lvlHeight = 0);
	
	//updates the camera to a specified point
	void updateCamera(int x, int y);

	//centers camera on a point
	void updateCamera(const SDL_Rect* object);

	//scales the camera to a given size
	void scaleCamera(int width, int height);

	//returns the camera's location
	SDL_Rect* &location();

	//destructor
	~Camera(void);
private:
	//The camera's position and size!
	SDL_Rect* gameCamera;
	int levelWidth, levelHeight, *winSizeCaptureW, *winSizeCaptureH;
};

#endif