#ifndef PLAYEROVERWORLD_H
#define PLAYEROVERWORLD_H

#include "PlayerParent.h"
class PlayerOverworld :
	public PlayerParent
{
public:
	PlayerOverworld();
	PlayerOverworld(int xPos, int yPos, int lwidth, int lheight);
	void handleEvents();
	void move();
	void render(SDL_Rect *camLoc);
	~PlayerOverworld();
private:
	//enumeration mirroring sfx array
	const enum soundEffects {footsteps, SFX_SIZE};

	//these two are temp until implementing ingame collision
	int levelWidth, levelHeight;
};

#endif