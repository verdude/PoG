#pragma once
#include <SDL.h>
#include "collision.h"
#include <vector>

using namespace std;

class Enemy : collision {
private:
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface* image;
	bool ground;
	SDL_Rect clips[2];
	double frame;
public:
	Enemy(SDL_Surface* img, int x, int y, int xVel, int yVel)
	{
		image = img;
		box.x = x;
		box.y = y;
		box.w = image->w / 2;
		box.h = image->h;
		xvel = xVel;
		yvel = yVel;
		ground = 0;
		//we set the clips for the image, so we can do animation, by blittin first one part of the image, than the other one
		for (int i = 0; i<2; i++)
		{
			clips[i].x = i * 40;
			clips[i].y = 0;
			clips[i].w = clips[i].h = 40;
		}
		frame = 0.0;      //initialize frame is 0
	}

	void Enemy::show(SDL_Surface* screen)
	{
		SDL_Rect tmp = { box.x - coord.x, box.y, 40, 40 };       //calculate the relative coordinate, so if the Enemy at 120px coordinate and the camera
		//at 100px coordinate, than we show it on 20px coordinate
		SDL_BlitSurface(image, &clips[(int)(frame + 0.5)], screen, &tmp);    //we just blit it. (int)(frame+0.5) is basically the round
	}

	SDL_Rect* Enemy::getRect()
	{
		return &box;
	}

	void Enemy::move(std::vector<std::vector<int> >& map) {
		int start = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE)) / baseclass::TILE_SIZE - 2;
		int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50 + 2;
		if (start<0)
			start = 0;
		if (end>map[0].size())
			end = map[0].size();
		bool falling = 0;      //if this remains 0 until the end of the loops, than we fall (no ground under the Enemy)
		for (int i = 0; i<map.size(); i++)//go through the map
			for (int j = start; j<end; j++)
			{
				if (map[i][j] == 0)
					continue;
				SDL_Rect destrect = { j * 50, i * 50, 50, 50 };
				if (collision_(&box, &destrect))   //if there was a collision
				{
					if (destrect.y >= box.y + box.h - 11)//and it'a the ground (so the tile is under the Enemy)
					{
						ground = 1;       //then we don't fall any more and we are on the ground
						yvel = 0;
						falling = 1;
					}
					else
						xvel = -xvel;     //else change the direction in the x axis
				}
			}
		if (!falling) //if there is no ground under the Enemy
			yvel = 5; //then fall

		box.x += xvel;    //just move
		box.y += yvel;
		frame += 0.1;     //and animate
		if (frame >= 1.4)  //if we're at frame 3
			frame = 0.0;      //set back
	}
};