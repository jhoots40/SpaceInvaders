#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "constants.h"
#include "functions.h"
#include "globals.h"
#include "pc.h"
#include "enemies.h"
#include "gamestate.h"
#include "text.h"


int main(int argc, char *argv[])
{
    
    //initialize SDL
    if(!init())
    {
        return -1;
    }
    
    //load files
    if(!loadMedia())
    {
        return -1;
    }
    
    //strting game state
    stateId = STATE_MAIN_GAME;
    currentState = new MainGame();
    
    while(stateId != STATE_EXIT)
    {
        //handle input for current state
        currentState->handleEvents();
        
        //handle logic for current state
        currentState->logic();
        
        //change state if needed
        change_state();
        
        //render current state
        currentState->render();
    }
    
    //clean up
    clean_up();
    
    return 0;
}

