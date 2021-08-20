#include "bullets.h"
#include "globals.h"
#include "functions.h"
#include "constants.h"
#include <stdexcept>

pcBullet::pcBullet()
{
    xPos_ = myPC.getX() + 16;
    yPos_ = myPC.getY() + 2;
    yVel_ = -10;
    
    bulletTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/pcBullet.png");
    if(bulletTexture_ == NULL)
        throw std::runtime_error("failed to load bullet texture");
    
    box_.x = xPos_;
    box_.y = yPos_;
    box_.w = 2;
    box_.h = 8;
}

pcBullet::~pcBullet()
{
    SDL_DestroyTexture(bulletTexture_);
    bulletTexture_ = NULL;
}

void pcBullet::move()
{
    yPos_ += yVel_;
    box_.y = yPos_;
}


void pcBullet::render()
{
    SDL_Rect renderQuad = {xPos_, yPos_, 2, 8};
    SDL_RenderCopy(renderer, bulletTexture_, NULL, &renderQuad);
}

bool pcBullet::outOfBounds()
{
    return yPos_ <= 0;
}

enemyBullet::enemyBullet()
{
    int rX, rY;
    while(1)
    {
        rX = rand() % 11;
        rY = rand() % 5;
        if(enemies[rX][rY] != NULL)
            break;
    }
    
    xPos_ = enemies[rX][rY]->getRect().x + (enemies[rX][rY]->getRect().w / 2);
    yPos_ = enemies[rX][rY]->getRect().y + enemies[rX][rY]->getRect().h;
    
    yVel_ = 7;
    
    bulletTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/enemyBullet.png");
    if(bulletTexture_ == NULL)
        throw std::runtime_error("failed to load enemy bullet texture");
    
    box_.x = xPos_;
    box_.y = yPos_;
    box_.w = 2;
    box_.h = 8;
}

enemyBullet::~enemyBullet()
{
    SDL_DestroyTexture(bulletTexture_);
    bulletTexture_ = NULL;
}

void enemyBullet::move()
{
    yPos_ += yVel_;
    box_.y = yPos_;
}

void enemyBullet::render()
{
    SDL_Rect renderQuad = {xPos_, yPos_, 2, 8};
    SDL_RenderCopy(renderer, bulletTexture_, NULL, &renderQuad);
}

bool enemyBullet::outOfBounds()
{
    return yPos_ >= 480;
}
