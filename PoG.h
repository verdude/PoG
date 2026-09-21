#pragma once

#include <vector>
#include <SDL3/SDL.h>

#include "Wrapper.h"
#include "themainbro.h"
#include "Timer.h"

using namespace std;

class PoG {
private:
	SDL_Rect camera;
	SDL_Window* window;
	SDL_Renderer* renderer;
	// matrix of the blocks
	vector<vector<int> > map;

	Wrapper* background;
	themainbro cherub;
	// direction the player is facing
	bool dir[2];
	static const int SC_WIDTH = 640;
	static const int SC_HEIGHT = 480;

	bool initialize() {
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}
		window = SDL_CreateWindow("PoG", SC_WIDTH, SC_HEIGHT, 0);
		if (window == NULL) {
			SDL_Log("Unable to create window: %s", SDL_GetError());
			return false;
		}
		renderer = SDL_CreateRenderer(window, NULL);
		if (renderer == NULL) {
			SDL_Log("Unable to create renderer: %s", SDL_GetError());
			return false;
		}
		if (!SDL_SetRenderVSync(renderer, 1)) {
			SDL_Log("VSync unavailable: %s", SDL_GetError());
		}
		return SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	bool loadImages() {
		return cherub.addSprite("chars/neutralright.png", renderer, 'r') &&
			cherub.addSprite("chars/walk1right.png", renderer, 'r') &&
			cherub.addSprite("chars/neutralleft.png", renderer, 'l') &&
			cherub.addSprite("chars/walk1left.png", renderer, 'l') &&
			background->loadFromFile("backdrops/cornfield.png", renderer);
	}

	void handEvents() {

	}

	void terminate() {
		cherub.clearSprites();
		delete background;
		background = NULL;
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_Quit();
	}

public:

	PoG() : camera(), window(NULL), renderer(NULL), background(new Wrapper()), cherub() {}

	~PoG() {
		terminate();
	}
	bool play() {
		if (!initialize()) {
			return false;
		}
		if (!loadImages()) {
			return false;
		}
		bool quit = false;
		SDL_Event e;
		// Timer to regulate movement of the main character
		Timer cherubTimer;

		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_EVENT_QUIT) {
					quit = true;
				}
				cherub.handle_input(e);
			}

			//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			double timeStep = cherubTimer.getTicks() / 1000.f;

			cherub.move(timeStep);
			
			cherubTimer.start();

			SDL_RenderClear(renderer);
			
			background->render(0, 0, renderer, false);
			cherub.show(renderer);
			
			SDL_RenderPresent(renderer);
		}
		return true;
	}
};
