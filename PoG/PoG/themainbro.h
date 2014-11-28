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
	SDL_Rect clips[4];
	vector<Wrapper> imgs;
	bool ground, jump;
	char direction;
	double frame;
	bool moving;
	int health;
public:
	// first load the images then 
	themainbro(vector<Wrapper> imgs) :
		imgs(imgs), box(), xvel(), yvel(), ground(), jump(), 
		direction('r'), frame(0.0), moving(), health(10)
	{
		box.w = 50;
		box.h = 100;
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

	}

	void show(Wrapper screen) {
		// render the image...
		// do i want to do it here?
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

};