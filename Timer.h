#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <sstream>

using namespace std;

class Timer {
private:
	Uint64 startTicks;
	Uint64 pausedTicks;
	bool paused;
	bool started;
public:
	Timer() : startTicks(), pausedTicks(), paused(false), started(false) {}

	void start() {
		started = true;
		paused = false;
		startTicks = SDL_GetTicks();
		pausedTicks = 0;
	}

	void stop() {
		started = false;
		paused = false;
		startTicks = 0;
		pausedTicks = 0;
	}

	void pause() {
		if (started && !paused) {
			paused = true;
			pausedTicks = SDL_GetTicks() - startTicks;
			startTicks = 0;
		}
	}

	void unpause() {
		if (started && paused) {
			paused = false;
			startTicks = SDL_GetTicks() - pausedTicks;
			pausedTicks = 0;
		}
	}

	Uint64 getTicks() {
		Uint64 time = 0;
		if (started) {
			if (paused) {
				time = pausedTicks;
			}
			else {
				time = SDL_GetTicks() - startTicks;
			}
		}
		return time;
	}

	bool isStarted() {
		return started;
	}

	bool isPaused() {
		return paused && started;
	}
};
