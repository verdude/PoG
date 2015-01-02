#pragma once

#include <SDL.h>
#include <SDL_image.h>
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
	Wrapper(SDL_Texture* texture = NULL) : 
		texture(texture), width(), height() {}
	~Wrapper() {
		free();
	}

	bool loadFromFile(string path, SDL_Renderer*& renderer) {
		free();
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else {
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else {
				width = loadedSurface->w;
				height = loadedSurface->h;
			}
			SDL_FreeSurface(loadedSurface);
		}
		texture = newTexture;
		return texture != NULL;
	}

	void free() {
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}

	void setColor(Uint8 red, Uint8 green, Uint8 blue) {

	}

	void setAlpha(Uint8 alpha) {

	}

	void render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL, 
		double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {

		SDL_Rect renderQuad = { x, y, width, height};
		SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}

	SDL_Texture* getTexture() {
		return texture;
	}

};