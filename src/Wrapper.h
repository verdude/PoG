#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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
	string name;

public:
	Wrapper(SDL_Texture* temp = NULL) : texture(temp), width(), height() {}
	~Wrapper() {
		free();
	}

	bool loadFromFile(string path, SDL_Renderer*& renderer) {
		// creates a hardware optimized texture and saves it in the private texture field
		free();
		name = path;
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			// printf("The image address: %p", loadedSurface);
			if (!SDL_SetSurfaceColorKey(loadedSurface, true,
			                            SDL_MapSurfaceRGB(loadedSurface, 0, 0xFF, 0xFF))) {
				printf("Unable to set color key for %s! SDL Error: %s\n", path.c_str(),
				       SDL_GetError());
				SDL_DestroySurface(loadedSurface);
				return false;
			}

			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
				       SDL_GetError());
			} else {
				SDL_SetTextureScaleMode(newTexture, SDL_SCALEMODE_LINEAR);
				width = loadedSurface->w;
				height = loadedSurface->h;
			}
			SDL_DestroySurface(loadedSurface);
		}
		texture = newTexture;
		return texture != NULL;
	}

	void free() {
		if (texture != NULL) {
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}

	void setColor(Uint8 red, Uint8 green, Uint8 blue) {}

	void setAlpha(Uint8 alpha) {}

	void render(int x, int y, SDL_Renderer*& renderer, bool log = false, SDL_Rect* clip = NULL,
	            double angle = 0.0, SDL_Point* center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE) {

		SDL_FRect renderQuad = {static_cast<float>(x), static_cast<float>(y),
		                        static_cast<float>(width), static_cast<float>(height)};
		if (!SDL_RenderTexture(renderer, texture, NULL, &renderQuad)) {
			printf("Error rendering texture [%s]: %s\n", name.c_str(), SDL_GetError());
		} else if (log) {
			printf("Rendering [%s]\n", name.c_str());
		}
	}

	int getHeight() {
		return height;
	}

	int getWidth() {
		return width;
	}

	string getName() {
		return name;
	}

	SDL_Texture* getTexture() {
		return texture;
	}

	void printAddress() {
		printf("Texture Address for [%s] : [%p]\n", name.c_str(), texture);
	}
};
