#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class PoG {
private:
	SDL_Surface *background, *screen, *block;
	SDL_Rect camera;
	SDL_Window* window;
	// matrix of the blocks
	vector<vector<int> > map;
	vector<SDL_Surface*> cherub;
	// direction the player is facing
	bool dir[2];
	static const int SC_WIDTH = 640;
	static const int SC_HEIGHT = 480;

	SDL_Surface* loadSurface(string path) {
		SDL_Surface* optimizedSurface = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			//printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, NULL);
			if (optimizedSurface != NULL) {
				//printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
				//SDL_SetColorKey(optimizedSurface, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF));
			}
			SDL_FreeSurface(loadedSurface);
		}
		return optimizedSurface;
	}

	SDL_Surface* loadImage(string s) {
		background = loadImage("cornfield.png");
		cherub.push_back(loadImage("larry.png"));
	}
	void loadMap(string filename) {

	}
	void showMap() {

	}
	void handEvents() {

	}
	void terminate() {
		SDL_FreeSurface(background);
		background = NULL;
		for (unsigned i = 0; i < cherub.size(); ++i) {
			SDL_FreeSurface(cherub[i]);
			cherub[i] = NULL;
		}
		cherub.clear();
		SDL_DestroyWindow(window);
		window = NULL;
		IMG_Quit();
		SDL_Quit();
	}

public:
	PoG() : cherub() {
		window = SDL_CreateWindow("PoG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
		screen = SDL_GetWindowSurface(window);
		camera.x = camera.y = 0;
	}
	~PoG() {
		terminate();
	}
	void play() {

	}
};