#include "globals.h"
#include "constants.h"

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

SDL_Event event;

PC myPC;

pcBullet *PCBullet = NULL;

enemyBullet *EBullet = NULL;

Enemy *enemies[11][5];

enum Direction d = RIGHT;

SDL_Rect enemyBox = {(SCREEN_WIDTH - 352) / 2, (SCREEN_HEIGHT - 350) / 2, 352, 150};

int stateId = STATE_NULL;
int nextState = STATE_NULL;

Uint32 timer = 0;

int frame = 0;

GameState *currentState = NULL;

TTF_Font *font = NULL;

Text *score;

Text *value;

std::vector<Defense *> def;
