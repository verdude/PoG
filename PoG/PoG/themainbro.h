#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Wrapper.h"
#include "collision.h"
#include "Timer.h"

using namespace std;

enum dir {
	DEFAULT,
	FACE_LEFT,
	FACE_RIGHT,
	NO_CHANGE
};

class themainbro : collision {
private:
	SDL_Rect box;
	double xvel, yvel;
	double xpos, ypos;
	vector<Wrapper> imgs;
	bool ground, jump;
	char direction;
	double frame;
	bool moving;
	int health;
	const double speed;
public:
	/*
	themainbro(vector<Wrapper> imgs) :
		imgs(imgs), box(), xvel(), yvel(), ground(), jump(), 
		direction('r'), frame(0.0), moving(), health(10)
	{
		box.w = 50;
		box.h = 100;
	}
	themainbro() :
		imgs(), box(), xvel(), yvel(), ground(), jump(),
		direction('r'), frame(0.0), moving(), health(10)
	{
		box.w = 50;
		box.h = 100;
	}*/
	/*set the width and height of the rect*/
	themainbro(int w = 50, int h = 100, vector<Wrapper> imgs = vector<Wrapper>()) :
		imgs(imgs), box(), xvel(), yvel(), ground(), jump(),
		direction('r'), frame(0.0), moving(), health(10), speed(1)
	{
		box.y = 480 - h;
		box.w = w;
		box.h = h;
	}

	~themainbro() {
		// free the wrapper...
		// I think it's automatic
	}

	SDL_Rect* getRect() {
		return &box;
	}

	void setXvel(int vel) {
		xvel = vel;
	}

	int getXvel() {
		return xvel;
	}

	void handle_input(SDL_Event& e) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym) {
				case SDLK_UP: yvel -= speed; break;
				case SDLK_DOWN: yvel += speed; break;
				case SDLK_LEFT: xvel -= speed; break;
				case SDLK_RIGHT: xvel += speed; break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			switch (e.key.keysym.sym) {
			case SDLK_UP: yvel += speed; break;
			case SDLK_DOWN: yvel -= speed; break;
			case SDLK_LEFT: xvel += speed; break;
			case SDLK_RIGHT: xvel -= speed; break;
			}
			/*if (newstate) apply_surface(x, y, AlexBird[1], screen);
			else apply_surface(x, y, AlexBird[1], screen);*/
		}
	}

	void move(const int& state, double t) {
		// needs to take parameters that will tell it which way to go
		box.x += xvel * t;
		if (box.x < 0) {
			box.x = 0;
		}
		else if (box.x > 640 - box.w) {
			box.x = 640 - box.w;
		}
		box.y += yvel;
		if (box.y < 0) {
			box.y = 0;
		}
		else if (box.y > 640 - box.h) {
			box.y = 640 - box.h;
		}
	}

	void show(SDL_Renderer*& renderer, const int& dir = DEFAULT) {
		imgs[dir].render(box.x, box.y, renderer);
	}

	void setJump() {
		/*if (ground && !jump) {
			jump = true;
			ground = false;
			yvel = -17; // the starting jump value
			box.y -= 5;
		}*/
	}

	void setMoving(bool b) {
		moving = b;
	}

	void setDirection(char c) {
		direction = c;
	}

	char getDirection() {
		return direction;
	}

	int getHealth() {
		return health;
	}

	void setHealth(int h) {
		health = h;
	}

	void addSprite(string filename, SDL_Renderer*& renderer) {
		Wrapper temp;
		imgs.push_back(temp);
		imgs[imgs.size() - 1].loadFromFile(filename, renderer);
		/* I'm not sure how to do error checking here. */

	}

	/*idk if this is necessary*/
	Wrapper getDefaultWrapper() {
		return imgs.size() ? imgs[0] : Wrapper();
	}

};