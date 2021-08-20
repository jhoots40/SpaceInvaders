#include "enemies.h"
#include "globals.h"
#include "functions.h"
#include "constants.h"
#include <stdexcept>

lowEnemy::lowEnemy(int x, int y) : xPos_(x), yPos_(y), isAlive(true)
{
    enemyTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/lowEnemy.png");
    box_.x = xPos_ + 4;
    box_.y = yPos_;
    box_.w = 24;
    box_.h = 16;
    
    score_ = 10;
    
    for(int i = 0; i < 3; i++)
    {
        SDL_Rect rect = {i * 16, 0, 16, 8};
        spriteClips_.push_back(rect);
    }
}

lowEnemy::~lowEnemy()
{
    SDL_DestroyTexture(enemyTexture_);
    enemyTexture_ = NULL;
}

void lowEnemy::move()
{
    if(d == RIGHT)
    {
        xPos_ += 8;
        box_.x = xPos_ + 4;
    }
    else if(d == LEFT)
    {
        xPos_ -= 8;
        box_.x = xPos_ + 4;
    }
    else if(d == DOWN)
    {
        yPos_ += 16;
        box_.y = yPos_;
    }
    
}

void lowEnemy::render(int frame)
{
    SDL_Rect renderQuad = {xPos_, yPos_, 32, 16};
    SDL_RenderCopy(renderer, enemyTexture_, &spriteClips_.at(frame), &renderQuad);
}

mediumEnemy::mediumEnemy(int x, int y) : xPos_(x), yPos_(y), isAlive(true)
{
    enemyTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/mediumEnemy.png");
    box_.x = xPos_ + 6;
    box_.y = yPos_;
    box_.w = 22;
    box_.h = 16;
    
    score_ = 20;
    
    for(int i = 0; i < 3; i++)
    {
        SDL_Rect rect = {i * 16, 0, 16, 8};
        spriteClips_.push_back(rect);
    }
}

mediumEnemy::~mediumEnemy()
{
    SDL_DestroyTexture(enemyTexture_);
    enemyTexture_ = NULL;
}

void mediumEnemy::move()
{
    if(d == RIGHT)
    {
        xPos_ += 8;
        box_.x = xPos_ + 6;
    }
    else if(d == LEFT)
    {
        xPos_ -= 8;
        box_.x = xPos_ + 6;
    }
    else if(d == DOWN)
    {
        yPos_ += 16;
        box_.y = yPos_;
    }
}

void mediumEnemy::render(int frame)
{
    SDL_Rect renderQuad = {xPos_, yPos_, 32, 16};
    SDL_RenderCopy(renderer, enemyTexture_, &spriteClips_.at(frame), &renderQuad);
}


highEnemy::highEnemy(int x, int y) : xPos_(x), yPos_(y), isAlive(true)
{
    enemyTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/highEnemy.png");
    box_.x = xPos_ + 8;
    box_.y = yPos_;
    box_.w = 16;
    box_.h = 16;
    
    score_ = 30;
    
    for(int i = 0; i < 3; i++)
    {
        SDL_Rect rect = {i * 16, 0, 16, 8};
        spriteClips_.push_back(rect);
    }
}

highEnemy::~highEnemy()
{
    SDL_DestroyTexture(enemyTexture_);
    enemyTexture_ = NULL;
}

void highEnemy::move()
{
    if(d == RIGHT)
    {
        xPos_ += 8;
        box_.x = xPos_ + 8;
    }
    else if(d == LEFT)
    {
        xPos_ -= 8;
        box_.x = xPos_ + 8;
    }
    else if(d == DOWN)
    {
        yPos_ += 16;
        box_.y = yPos_;
    }
}

void highEnemy::render(int frame)
{
    SDL_Rect renderQuad = {xPos_, yPos_, 32, 16};
    SDL_RenderCopy(renderer, enemyTexture_, &spriteClips_.at(frame), &renderQuad);
}

