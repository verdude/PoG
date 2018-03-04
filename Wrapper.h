#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
	Wrapper(SDL_Texture* temp = NULL) : 
		texture(temp), width(), height() {}
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
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else {
            //printf("The image address: %p", loadedSurface);
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

	void render(int x, int y, SDL_Renderer*& renderer, bool log = false, SDL_Rect* clip = NULL, 
		double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {

		SDL_Rect renderQuad = { x, y, width, height};
		int code = SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
        if (code < 0) {
            printf("Error rendering Texture [%s]. Got Error code: [%i]\n", name.c_str(), code);
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
