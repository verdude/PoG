#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Wrapper.h"
#include "collision.h"

using namespace std;

typedef struct keys_pressed {
    bool left;
    bool right;
    bool up;
    bool down;
} keys_pressed;

typedef struct jump_vals {
    bool jumping;
    bool grounded;
    unsigned jump_height;
    double prev_jump_height;
    unsigned max_jump_duration;
    double jump_duration;
    double jump_start;
} jump_vals;

class themainbro : collision {
private:
    SDL_Rect box;
    float xvel, yvel;
    float xpos, ypos;
    vector<Wrapper*> rightImgs;
    vector<Wrapper*> leftImgs;
    char direction;
    int health;
    const double speed;
    keys_pressed keys;
    jump_vals jmp_ctrl;
    unsigned int frame;
    unsigned int totalFrames;
public:
    /*set the width and height of the rect*/
    themainbro() :
        rightImgs(), leftImgs(), box(), xvel(), yvel(),
        direction('r'), health(10), speed(300), keys(), frame(), totalFrames(), jmp_ctrl()
    {
        jmp_ctrl.jumping = false;
        jmp_ctrl.grounded = true;
        jmp_ctrl.jump_height = 100;
        jmp_ctrl.max_jump_duration = 500;
        jmp_ctrl.jump_duration = 0;
        jmp_ctrl.prev_jump_height = 0;
        jmp_ctrl.jump_start = 0;

        box.y = 480 - 77;
        box.x = 0;
        box.w = 0;
        box.h = 0;

        ypos = box.y;
        xpos = box.x;
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
            //case SDLK_UP: yvel -= speed; break;
            //case SDLK_DOWN: yvel += speed; break;
            case SDLK_LEFT:
                    xvel -= speed;
                    if (!keys.right) direction = 'l';
                    keys.left = true;
                    break;
            case SDLK_RIGHT:
                    xvel += speed;
                    if (!keys.left) direction = 'r';
                    keys.right = true;
                    break;
            case SDLK_SPACE:
                    set_jump();
                    break;
            }
        }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym) {
            //case SDLK_UP: yvel += speed; break;
            //case SDLK_DOWN: yvel -= speed; break;
            case SDLK_LEFT:
                    xvel += speed;
                    if (keys.right) direction = 'r';
                    keys.left = false;
                    break;
            case SDLK_RIGHT:
                    xvel -= speed;
                    if (keys.left) direction = 'l';
                    keys.right = false;
                    break;
            }
        }
    }

    void move(const float timeStep) {
        xpos += xvel * timeStep;
        box.x = (int)xpos;
        if (box.x < 0) {
            xpos = 0;
        }
        if (box.x + box.w > 640) {
            xpos = 640 - box.w;
        }
        handle_jump(timeStep);
        ypos += yvel;
        box.y = (int)ypos;
        if (box.y < 0) {
            ypos = 0;
        }
        if (box.y + box.h > 480) {
            ypos = 480 - box.h;
        }
    }

    void show(SDL_Renderer*& renderer) {
        frame++;
        unsigned interval = 800;
        if (frame / interval >= totalFrames)
            frame = 0;

        unsigned i = keys.right || keys.left ? frame / interval : 0;

        if (direction == 'r') {
            if (rightImgs[i]->getWidth() != box.w)
                box.w = rightImgs[i]->getWidth();
            rightImgs[i]->render((int)xpos, (int)ypos, renderer);
        }
        else {
            if (leftImgs[i]->getWidth() != box.w)
                box.w = leftImgs[i]->getWidth();
            leftImgs[i]->render((int)xpos, (int)ypos, renderer);
        }
    }

    void set_jump() {
        if (jmp_ctrl.grounded && !jmp_ctrl.jumping) {
            jmp_ctrl.jumping = true;
            jmp_ctrl.grounded = false;
            jmp_ctrl.jump_start = box.y;
        }
    }

    void jump_reset() {
        jmp_ctrl.jumping = false;
        jmp_ctrl.grounded = true;
        jmp_ctrl.jump_height = 100;
        jmp_ctrl.max_jump_duration = 500;
        jmp_ctrl.jump_duration = 0;
        jmp_ctrl.prev_jump_height = 0;
        jmp_ctrl.jump_start = 0;
    }

    double calc_vertical_location_in_jump(float milliseconds) {
        if (jmp_ctrl.jumping && !jmp_ctrl.grounded) {
            // negative means increase
            jmp_ctrl.jump_duration += milliseconds;
            if (jmp_ctrl.jump_duration >= jmp_ctrl.max_jump_duration) {
                // the time of the jump is over, they should stop jumping
                jump_reset();
                return 0.0;
            }
            double height_at_time = .0032 * jmp_ctrl.jump_duration - .8; 
            double height = height_at_time - jmp_ctrl.prev_jump_height;
            jmp_ctrl.prev_jump_height = height;
            return height;
        }
        else {
            printf("Shouldn't get here.\n");
            return 0.0;
        }
    }

    // timeStep is the number of seconds that have passed since
    // the last frame
    void handle_jump(float timeStep) {
        // convert back to milliseconds
        timeStep *= 1000;
        if (jmp_ctrl.jumping && !jmp_ctrl.grounded) {
            yvel = calc_vertical_location_in_jump(timeStep);
        } else {
            jump_reset();
            //yvel = 0;
        }
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
            totalFrames++;
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
