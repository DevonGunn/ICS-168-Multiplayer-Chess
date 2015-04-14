#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

//Timer class which is used for timing :P and managing frame rate
class Timer
{
public:
	Timer(void);

	//starts the timer
	void start();
	//stops the timer
	void stop();
	//pauses the timer
	void pause();
	//unpauses the timer
	void unpause();

	//Getters
	
	//getTicks - returns the timer's current ticks
	//@return int - the timer's current ticks
	int getTicks();

	//isStarted - returns whether the timer is started or not
	//@return bool - whether timer is started or not
	bool isStarted();

	//isPaused - returns whether the timer is paused or not
	//@return bool - whether the time is paused or not
	bool isPaused();

	~Timer(void);
private:
	int startTicks, pausedTicks;
	bool paused, started;
};

#endif