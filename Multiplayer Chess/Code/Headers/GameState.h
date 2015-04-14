#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	virtual void handleEvents() = 0;

	virtual void logic() = 0;

	virtual void render() = 0;

	virtual ~GameState(void){};
};

#endif