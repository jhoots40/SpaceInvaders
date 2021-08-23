#ifndef DEFENSE_H
#define DEFENSE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

class Defense
{
public:
    Defense(int x, int y);
    ~Defense();
    void render();
    SDL_Rect getRect() {return box_;}
    int health;
private:
    SDL_Rect box_;
    SDL_Texture *defenseTexture_;
    std::vector<SDL_Rect> spriteClips_;
};

#endif
