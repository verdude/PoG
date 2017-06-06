#pragma once

#include <SDL2/SDL.h>

using namespace std;

enum dir {
	DEFAULT,
	FACE_LEFT,
	FACE_RIGHT,
	NO_CHANGE
};

class collision {
protected:
	static SDL_Rect coord;
	static const int tileSize = 50;

	bool collision_(SDL_Rect* rec1, SDL_Rect* rec2) {
		if (rec1->y >= rec2->y + rec2->h)
			return 1;
		if (rec1->x >= rec2->x + rec2->w)
			return 1;
		if (rec1->y + rec1->h <= rec2->y)
			return 1;
		if (rec1->x + rec1->w <= rec2->x)
			return 1;
		return 0;
	}
public:
	collision(){}
	~collision(){}
};
