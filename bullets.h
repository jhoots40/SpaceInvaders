#ifndef BULLETS_H
#define BULLETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bullet
{
public:
    virtual void move() = 0;
    virtual void render() = 0;
    virtual ~Bullet() {};
};

class pcBullet : public Bullet
{
public:
    pcBullet();
    ~pcBullet();
    void move();
    void render();
    bool outOfBounds();
    SDL_Rect getRect() {return box_;}
private:
    int xPos_, yPos_;
    int yVel_;
    SDL_Texture *bulletTexture_;
    SDL_Rect box_;
};

class enemyBullet : public Bullet
{
public:
    enemyBullet();
    ~enemyBullet();
    void move();
    void render();
    bool loadTexture();
    bool outOfBounds();
    SDL_Rect getRect() {return box_;}
private:
    int xPos_, yPos_;
    int xVel_, yVel_;
    SDL_Texture *bulletTexture_;
    SDL_Rect box_;
};

#endif
