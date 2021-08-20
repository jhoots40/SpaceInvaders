#include "functions.h"
#include "globals.h"
#include "constants.h"


bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }
    
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        return false;
    }
    
    if(!IMG_Init(IMG_INIT_PNG))
    {
        return false;
    }
    
    if( TTF_Init() == -1 )
    {
        return false;
    }
    
    return true;
}

bool loadMedia()
{
    
    font = TTF_OpenFont("space_invaders.ttf", 28);
    if(font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    
    return true;
}

bool loadEnemies()
{
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(j >= 3)
                enemies[i][j] = new lowEnemy(((SCREEN_WIDTH - 352) / 2) + (i * 32), ((SCREEN_HEIGHT - 350) / 2) + j * 30);
            else if(j >= 1)
                enemies[i][j] = new mediumEnemy(((SCREEN_WIDTH - 352) / 2) + (i * 32),((SCREEN_HEIGHT - 350) / 2) + j * 30);
            else
                enemies[i][j] = new highEnemy(((SCREEN_WIDTH - 352) / 2) + (i * 32), ((SCREEN_HEIGHT - 350) / 2) + j * 30);
        }
    }
    return true;
}

SDL_Texture *getTexture(std::string path)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
        throw std::runtime_error("Failed to load surface");
    
    SDL_Texture *loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(loadedTexture == NULL)
        printf("failed! Error: %s\n", SDL_GetError());
    
    SDL_FreeSurface(loadedSurface);
    
    return loadedTexture;
}

bool check_collision(SDL_Rect A, SDL_Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void updateDirection()
{
   if(d == DOWN)
   {
       if(enemyBox.x <= 0)
           d = RIGHT;
       else if(enemyBox.x + enemyBox.w >= SCREEN_WIDTH)
           d = LEFT;
       
       return;
   }
    
    if(enemyBox.x <= 0 || enemyBox.x + enemyBox.w >= SCREEN_WIDTH)
        d = DOWN;
    
    return;
}

void updateEnemyBox()
{
    if(d == RIGHT)
        enemyBox.x += 8;
    else if(d == LEFT)
        enemyBox.x -= 8;
    else if(d == DOWN)
        enemyBox.y += 16;
}

void clean_up()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(enemies[i][j] != NULL)
            {
                enemies[i][j]->~Enemy();
                enemies[i][j] = NULL;
            }
        }
    }
    
    delete currentState;
    delete PCBullet;
    delete EBullet;
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    if(nextState != STATE_NULL)
    {
        if(nextState != STATE_EXIT)
        {
            delete currentState;
        }
        
        switch(nextState)
        {
            case STATE_MAIN_GAME:
                printf("made it here\n");
                currentState = new MainGame();
                break;
            case STATE_GAME_OVER:
                currentState = new GameOver();
                break;
        }
        
        stateId = nextState;
        nextState = STATE_NULL;
    }
}
