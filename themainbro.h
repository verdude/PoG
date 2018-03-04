#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Wrapper.h"
#include "collision.h"

#include <iostream>

using namespace std;

class themainbro : collision {
private:
    SDL_Rect box;
    float xvel, yvel;
    float xpos, ypos;
    vector<Wrapper*> rightImgs;
    vector<Wrapper*> leftImgs;
    bool ground, jump;
    char direction;
    double frame;
    bool moving;
    int health;
    const double speed;
public:
    /*set the width and height of the rect*/
    themainbro(int w = 50, int h = 100) :
        rightImgs(), leftImgs(), box(), xvel(), yvel(), ground(), jump(),
        direction('r'), frame(0.0), moving(), health(10), speed(300)
    {
        box.y = 480 - h;
        box.x = 0;
        ypos = box.y;
        xpos = box.x;
        box.w = w;
        box.h = h;
    }

    ~themainbro() {
        for (int i = 0; i < rightImgs.size(); i++)
            delete rightImgs[i];

        for (int i = 0; i < leftImgs.size(); i++)
            delete leftImgs[i];
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

    void handle_input(SDL_Event e) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym) {
            case SDLK_UP: yvel -= speed; break;
            case SDLK_DOWN: yvel += speed; break;
            case SDLK_LEFT:
                    xvel -= speed;
                    direction = 'l';
                    break;
            case SDLK_RIGHT:
                    xvel += speed;
                    direction = 'r';
                    break;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym) {
            case SDLK_UP: yvel += speed; break;
            case SDLK_DOWN: yvel -= speed; break;
            case SDLK_LEFT:
                    xvel += speed;
                    direction = 'l';
                    break;
            case SDLK_RIGHT:
                    xvel -= speed;
                    direction = 'r';
                    break;
            }
        }
    }

    void move(const int& state, const float timeStep) {
        xpos += xvel * timeStep;
        box.x = (int)xpos;
        if (box.x < 0) {
            xpos = 0;
        }
        if (box.x + box.w > 640) {
            xpos = 640 - box.w;
        }
        ypos += yvel * timeStep;
        box.y = (int)ypos;
        if (box.y < 0) {
            ypos = 0;
        }
        if (box.y + box.h > 480) {
            ypos = 480 - box.h;
        }
    }

    void show(SDL_Renderer*& renderer, const int& dir = DEFAULT) {
        //printf("Showing [%s] with dimensions: [%ix%i] and box dimensions of :[ixi]\n", imgs[0].getName().c_str(), imgs[0].getWidth(), imgs[0].getHeight());
        if (direction == 'r') {
            rightImgs[0]->render((int)xpos, (int)ypos, renderer);
        }
        else {
            leftImgs[0]->render((int)xpos, (int)ypos, renderer);
        }
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

    void addSprite(string filename, SDL_Renderer*& renderer, char dir) {
        Wrapper* temp = new Wrapper();
        temp->loadFromFile(filename, renderer);

        if (dir == 'r') {
            rightImgs.push_back(temp);
        }
        else {
            leftImgs.push_back(temp);
        }
    }

    Wrapper* getDefaultWrapper() {
        return direction == 'r' ? (rightImgs.size() > 0 ? rightImgs[0] : NULL) : (leftImgs.size() > 0 ? leftImgs[0] : NULL);
    }

    void printImgAddresses() {
        for (unsigned i = 0; i < rightImgs.size(); i++) {
            rightImgs[i]->printAddress();
        }
        for (unsigned i = 0; i < leftImgs.size(); i++) {
            leftImgs[i]->printAddress();
        }
    }

};
