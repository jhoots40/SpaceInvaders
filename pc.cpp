#include "pc.h"
#include "globals.h"
#include "constants.h"
#include "functions.h"


PC::PC() : xPos_((SCREEN_WIDTH - PC_WIDTH) / 2), yPos_(SCREEN_HEIGHT - 64), xVel_(0), yVel_(0)
{
    box_.x = xPos_ + 2;
    box_.y = yPos_ + 2;
    box_.w = 28;
    box_.h = 14;
}

PC::~PC()
{
    left_ = false;
    right_ = false;
    SDL_DestroyTexture(pcTexture_);
    pcTexture_ = NULL;
}

void PC::render()
{
    SDL_Rect renderQuad = {xPos_, yPos_, 32, 16};
    SDL_RenderCopy(renderer, pcTexture_, NULL, &renderQuad);
}

bool PC::loadTexture()
{
    pcTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/pc.png");
    return pcTexture_ != NULL;
}

void PC::handleInput()
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
            right_ = true;
        }
        else if(event.key.keysym.sym == SDLK_LEFT)
        {
            left_ = true;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
            right_ = false;
        }
        else if(event.key.keysym.sym == SDLK_LEFT)
        {
            left_ = false;
        }
    }
}

void PC::move()
{
    updateVelocity();
    
    xPos_ += xVel_;
    if(xPos_ + PC_WIDTH > SCREEN_WIDTH || xPos_ < 0)
    {
        xPos_ -= xVel_;
    }
    
    yPos_ += yVel_;
    if(yPos_ + PC_HEIGHT > SCREEN_HEIGHT || yPos_ < 0)
    {
        yPos_ -= yVel_;
    }
    
    box_.x = xPos_ + 2;
    box_.y = yPos_ + 2;
}

void PC::updateVelocity()
{
    if(left_)
        xVel_ = -5;
    else if(right_)
        xVel_ = 5;
    else
        xVel_ = 0;
}


