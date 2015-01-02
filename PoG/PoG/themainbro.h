#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Wrapper.h"
#include "collision.h"

using namespace std;

enum dir {
	DEFAULT,
	FACE_LEFT,
	FACE_RIGHT
};

class themainbro : collision {
private:
	SDL_Rect box;
	int xvel, yvel;
	int xpos, ypos;
	vector<Wrapper> imgs;
	bool ground, jump;
	char direction;
	double frame;
	bool moving;
	int health;
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
		direction('r'), frame(0.0), moving(), health(10)
	{
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

	void move() {
		// needs to take parameters that will tell it which way to go
		box.x += xvel;
		if ((box.x < 0) || (box.x + box.w > 640)) {
			box.x -= xvel;
		}
		box.y += yvel;
		if ((box.y < 0) || (box.y + box.h > 480)) {
			box.y -= yvel;
		}
	}

	void show(SDL_Renderer*& renderer, const int& dir = DEFAULT) {
		imgs[dir].render(box.x, box.y, renderer);
	}

	void setJump() {
		if (ground && !jump) {
			jump = true;
			ground = false;
			yvel = -17; // the starting jump value
			box.y -= 5;
		}
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

	int Ystart() {
		return 480 - box.h;
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