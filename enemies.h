#ifndef ENEMIES_H
#define ENEMIES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Enemy
{
public:
    virtual void move() = 0;
    virtual void render(int frame) = 0;
    virtual SDL_Rect getRect() = 0;
    virtual ~Enemy() {};
    virtual bool getIsAlive() = 0;
    virtual void setIsAlive(bool b) = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    int score_;
};

class lowEnemy : public Enemy
{
public:
    lowEnemy(int x, int y);
    ~lowEnemy();
    void move();
    void render(int frame);
    SDL_Rect getRect() {return box_;}
    bool getIsAlive() {return isAlive;}
    void setIsAlive(bool b) {isAlive = b;}
    int getX() {return xPos_;}
    int getY() {return yPos_;}
private:
    int xPos_, yPos_;
    SDL_Rect box_;
    SDL_Texture *enemyTexture_;
    std::vector<SDL_Rect> spriteClips_;
    bool isAlive;
};

class mediumEnemy : public Enemy
{
public:
    mediumEnemy(int x, int y);
    ~mediumEnemy();
    void move();
    void render(int frame);
    SDL_Rect getRect() {return box_;}
    bool getIsAlive() {return isAlive;}
    void setIsAlive(bool b) {isAlive = b;}
    int getX() {return xPos_;}
    int getY() {return yPos_;}
private:
    int xPos_, yPos_;
    SDL_Rect box_;
    SDL_Texture *enemyTexture_;
    std::vector<SDL_Rect> spriteClips_;
    bool isAlive;
};

class highEnemy : public Enemy
{
public:
    highEnemy(int x, int y);
    ~highEnemy();
    void move();
    void render(int frame);
    SDL_Rect getRect() {return box_;}
    bool getIsAlive() {return isAlive;}
    void setIsAlive(bool b) {isAlive = b;}
    int getX() {return xPos_;}
    int getY() {return yPos_;}
private:
    int xPos_, yPos_;
    SDL_Rect box_;
    SDL_Texture *enemyTexture_;
    std::vector<SDL_Rect> spriteClips_;
    bool isAlive;
};

#endif
