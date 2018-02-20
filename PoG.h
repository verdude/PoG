#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Wrapper.h"
#include "themainbro.h"
#include "Timer.h"

using namespace std;

class PoG {
private:
	SDL_Surface *screen, *block;
	SDL_Rect camera;
	SDL_Window* window;
	SDL_Renderer* renderer;
	// matrix of the blocks
	vector<vector<int> > map;

	Wrapper background;
	themainbro cherub;
	// direction the player is facing
	bool dir[2];
	static const int SC_WIDTH = 640;
	static const int SC_HEIGHT = 480;

	bool initialize() {
		bool success = true;
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			success = false;
		} else {
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			window = SDL_CreateWindow("PoG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				success = false;
			} else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL) {
					success = false;
				} else {
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						success = false;
					}
				}
			}
		}
		return success;
	}

	bool loadImages() {
		bool success = true;
		cherub.addSprite("chars/cherubim.png", renderer);
		background.loadFromFile("backdrops/cornfield.png", renderer);
		return success;
	}

	void handEvents() {

	}

	void terminate() {
		SDL_DestroyWindow(window);
		window = NULL;
		IMG_Quit();
		SDL_Quit();
	}

	int getKeyStates() {
		//themainbro curr = NULL;
		const Uint8* currState = SDL_GetKeyboardState(NULL);
		if (currState[SDL_SCANCODE_UP])
		{
			return DEFAULT;
		}
		else if (currState[SDL_SCANCODE_DOWN])
		{
			return DEFAULT;
		}
		else if (currState[SDL_SCANCODE_LEFT])
		{
			return DEFAULT;
		}
		else if (currState[SDL_SCANCODE_RIGHT])
		{
			return DEFAULT;
		}
		else
		{
			return DEFAULT;
		}
	}

public:

	PoG() : background(), cherub(80, 80) {
		screen = SDL_GetWindowSurface(window);
		camera.x = camera.y = 0;
	}
	~PoG() {
		terminate();
	}
	void play() {
		if (!initialize()) {
			//system("PAUSE");
			return;
		}
		if (!loadImages()) {
			//system("PAUSE");
			return;
		}
		bool quit = false;
		SDL_Event e;
		int state = 0;
		// Timer to regulate movement of the main character
		Timer cherubTimer;

		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				cherub.handle_input(e);
			}

			//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			double timeStep = cherubTimer.getTicks() / 1000.f;

			cherub.move(state, timeStep);
			
			cherubTimer.start();

			SDL_RenderClear(renderer);
			
			background.render(0, 0, renderer);
			cherub.show(renderer, state);
			
			SDL_RenderPresent(renderer);
			
			state = getKeyStates();
		}
	}
};
