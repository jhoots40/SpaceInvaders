#ifndef PC_H
#define PC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class PC
{
public:
    PC();
    ~PC();
    void handleInput();
    void move();
    void render();
    void updateVelocity();
    bool loadTexture();
    SDL_Rect getRect() {return box_;}
    int getX() {return xPos_;}
    int getY() {return yPos_;}
private:
    int xPos_, yPos_;
    int xVel_, yVel_;
    SDL_Rect box_;
    SDL_Texture *pcTexture_;
    bool left_, right_;
};

#endif
