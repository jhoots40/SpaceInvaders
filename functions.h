#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//File loading
bool loadMedia();

//EnemyLoading
bool loadEnemies();

//update enemy direction
void updateDirection();

//update enemy box
void updateEnemyBox();

//image loader
SDL_Texture *getTexture(std::string path);

//Initialization
bool init();

//clean up
void clean_up();

//state status manager
void set_next_state(int newState);

//state changer
void change_state();

//collision checker using rectangles
bool check_collision(SDL_Rect A, SDL_Rect B);

#endif
