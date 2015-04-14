#include "Timer.h"


Timer::Timer(void)
{
	//initial initialization
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}


void Timer::start()
{
	//set started to true and ensure timer is unpaused
	paused = false;
	started = true;

	//start timer last to ensure most accurate ticks
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//stop the timer
	started = false;
	paused = false;
}

void Timer::pause()
{
	//if the timer is started, but not already paused
	if (started == true && paused == false)
	{
		//pause the timer
		paused = true;

		//calculate how many ticks recorded thusfar by the timer
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//if the timer is started, and paused
	if (started == true && paused == true)
	{
		//unpause
		paused = false;

		//set the start ticks so as if we had never paused
		startTicks = SDL_GetTicks() - pausedTicks;

		//set paused ticks to 0 for good housekeeping
		pausedTicks = 0;
	}
}

int Timer::getTicks()
{
	//check to see if the timer is started
	if (started == true)
	{
		//if the timer is paused, return the paused time
		if (paused == true)
		{
			return pausedTicks;
		}
		//return current time if timer is unpaused
		else return SDL_GetTicks() - startTicks;
	}

	//if the timer isn't started, return 0
	return 0;
}

bool Timer::isStarted()
{
	//return whether or not timer is started
	return started;
}


bool Timer::isPaused()
{
	//return whether or not timer is paused
	return paused;
}

Timer::~Timer(void)
{
}
