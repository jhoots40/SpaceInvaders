#include "defense.h"
#include "globals.h"
#include "constants.h"
#include "functions.h"

Defense::Defense(int x, int y)
{
    defenseTexture_ = getTexture("/Users/houtsjake/projectsCPP/spaceInvaders/sprites/fulldefense.png");
    box_.x = x;
    box_.y = y;
    box_.w = 12;
    box_.h = 12;
    health = 3;
    
    
    for(int i = 0; i < 4; i++)
    {
        SDL_Rect rect = {i * 12, 0, 12, 12};
        spriteClips_.push_back(rect);
    }
}

Defense::~Defense()
{
    SDL_DestroyTexture(defenseTexture_);
    defenseTexture_ = NULL;
}

void Defense::render()
{
    SDL_RenderCopy(renderer, defenseTexture_, &spriteClips_.at(health), &box_);
}


