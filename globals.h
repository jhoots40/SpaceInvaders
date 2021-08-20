#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "pc.h"
#include "enemies.h"
#include "bullets.h"
#include "gamestate.h"
#include "text.h"

extern SDL_Renderer *renderer;
extern SDL_Window *window;

extern SDL_Event event;

extern PC myPC;

extern Enemy *enemies[11][5];

extern SDL_Rect enemyBox;

extern pcBullet *PCBullet;

extern enemyBullet *EBullet;

enum Direction {
    RIGHT,
    LEFT,
    DOWN
};

extern enum Direction d;

enum GameStates {
    STATE_NULL,
    STATE_MAIN_MENU,
    STATE_MAIN_GAME,
    STATE_GAME_OVER,
    STATE_EXIT
};

extern int stateId;
extern int nextState;

extern Uint32 timer;
extern int frame;

extern GameState *currentState;

extern TTF_Font *font;

#endif
