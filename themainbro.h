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
    double jump_start;
    double jump_time;
    double function_coefficient;
    double zero_1;
    double zero_2;
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
    unsigned int frame;
    unsigned int totalFrames;
    jump_vals jmp_ctrl;
    unsigned max_jump_duration;
    unsigned jump_height;

    /**
     * y = a(x-z1)(x-z2)
     * z1 and z2 are the zeroes of the parabola
     */
    void calc_jump_function_coefficient(double z1, double z2, double x, double y) {
        jmp_ctrl.function_coefficient = y / ((x - z1) * (x - z2));

        printf("z1: %f, z2: %f x: %f y: %f\n", z1, z2, x, y);
        printf("a: %f\n", jmp_ctrl.function_coefficient);
    }

    void jump_reset() {
        jmp_ctrl.jumping = false;
        jmp_ctrl.grounded = true;
        jmp_ctrl.jump_time = 0;
        jmp_ctrl.jump_start = 0;
    }

    void set_jump() {
        if (jmp_ctrl.grounded && !jmp_ctrl.jumping) {
            jmp_ctrl.jumping = true;
            jmp_ctrl.grounded = false;
            jmp_ctrl.jump_start = box.y;
        }
    }

    double calc_vertical_location_in_jump(float milliseconds) {
        if (jmp_ctrl.jumping && !jmp_ctrl.grounded) {
            // negative means increase
            jmp_ctrl.jump_time += milliseconds;
            if (jmp_ctrl.jump_time >= max_jump_duration) {
                // the time of the jump is over, they should stop jumping
                jump_reset();
                return jmp_ctrl.jump_start;
            }
            double ypos = jmp_ctrl.function_coefficient * (jmp_ctrl.jump_time - jmp_ctrl.zero_1) * (jmp_ctrl.jump_time - jmp_ctrl.zero_2);
            double height = jmp_ctrl.jump_start + ypos;
            printf("height: %f\n", height);
            return height;
        }
        else {
            printf("Shouldn't get here.\n");
            jump_reset();
            return jmp_ctrl.jump_start;
        }
    }

    // timeStep is the number of seconds that have passed since
    // the last frame
    double handle_jump(float timeStep) {
        // convert back to milliseconds
        timeStep *= 1000;
        if (jmp_ctrl.jumping && !jmp_ctrl.grounded) {
            return jmp_ctrl.jump_start + calc_vertical_location_in_jump(timeStep);
        } else {
            jump_reset();
            return jmp_ctrl.jump_start;
        }
    }

public:
    /*set the width and height of the rect*/
    themainbro(double start = 0, double jump_duration = 500, double jump_height = -100) :
        rightImgs(), leftImgs(), box(), xvel(), yvel(), direction('r'), health(10), speed(300),
        keys(), frame(), totalFrames(), jmp_ctrl(), jump_height(jump_height), max_jump_duration(jump_duration)
    {
        jmp_ctrl.zero_1 = start;
        jmp_ctrl.zero_2 = jump_duration;
        jump_reset();

        double jump_midpoint = ((jump_duration - start)/2) + start;

        calc_jump_function_coefficient(start, jump_duration, jump_midpoint, jump_height);

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
        ypos = handle_jump(timeStep);
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
            box.w = rightImgs[i]->getWidth();
            box.h = rightImgs[i]->getHeight();
            rightImgs[i]->render((int)xpos, (int)ypos, renderer);
        }
        else {
            box.w = leftImgs[i]->getWidth();
            box.h = leftImgs[i]->getHeight();
            leftImgs[i]->render((int)xpos, (int)ypos, renderer);
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
