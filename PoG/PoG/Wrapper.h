#pragma once

#include <SDL.h>
#include <string>

using namespace std;

/*
	Used as a wrapper for textures. This makes it easy to... do... something...
*/

class Wrapper {
private:
	SDL_Texture* texture;
	int width;
	int height;
public:
	Wrapper() : texture(NULL), width(), height() {}
	~Wrapper(){}

	bool loadFromFile(string path) {

	}

	void free() {

	}

	void setColor(Uint8 red, Uint8 green, Uint8 blue) {

	}

	void setAlpha(Uint8 alpha) {

	}

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {

	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}

};