#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Wrapper.h"
#include "themainbro.h"

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
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
		background.loadFromFile("cornfield.png", renderer);

		return success;
	}

	void loadMap(string filename) {

	}
	void showMap() {

	}
	void handEvents() {

	}
	void terminate() {
		SDL_DestroyWindow(window);
		window = NULL;
		IMG_Quit();
		SDL_Quit();
	}

	void getKeyStates() {
		//themainbro curr = NULL;
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			// change the velocity
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			// change the velocity
		}
		else if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			// change the velocity	
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			
		}
		else
		{
			
		}
	}

public:

	PoG() : background(), cherub() {
		screen = SDL_GetWindowSurface(window);
		camera.x = camera.y = 0;
	}
	~PoG() {
		terminate();
	}
	void play() {
		if (!initialize()) {
			system("PAUSE");
			return;
		}
		if (!loadImages()) {
			system("PAUSE");
			return;
		}
		bool quit = false;
		SDL_Event e;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			getKeyStates();

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			background.render(0, 0, renderer);

			SDL_RenderPresent(renderer);
		}
	}
};