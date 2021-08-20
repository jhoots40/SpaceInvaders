#include "gamestate.h"
#include "globals.h"
#include "functions.h"
#include "constants.h"
#include "text.h"

MainGame::MainGame()
{
    d = RIGHT;
    
    points_ = 0;
    
    enemyBox.x = (SCREEN_WIDTH - 352) / 2;
    enemyBox.y = (SCREEN_HEIGHT - 350) / 2;
    enemyBox.w = 352;
    enemyBox.h = 150;
    
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(enemies[i][j] != NULL)
            {
                delete enemies[i][j];
                enemies[i][j] = NULL;
            }
        }
    }
    if(!loadEnemies())
    {
        throw std::runtime_error("Failed to load enemies");
    }
    
    if(!myPC.loadTexture())
    {
        throw std::runtime_error("Failed to load PC");
    }
    
    SDL_Color white = {255, 255, 255};
    score_ = new Text("Score: ", white, 20);
    value_ = new Text("0", white, 20);
}
MainGame::~MainGame()
{
    if(EBullet != NULL)
    {
        delete EBullet;
        EBullet = NULL;
    }
    if(PCBullet != NULL)
    {
        delete PCBullet;
        PCBullet = NULL;
    }
    
    myPC.~PC();
}

void MainGame::handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            set_next_state(STATE_EXIT);
        }
        if(event.type == SDL_KEYDOWN)
        {
            //if space if pressed fire a new bullet
            if(event.key.keysym.sym == SDLK_SPACE && PCBullet == NULL)
            {
                PCBullet = new pcBullet();
            }
        }
        
        //handle input for pc
        myPC.handleInput();
    }
}

void MainGame::logic()
{
    if(EBullet == NULL)
    {
        EBullet = new enemyBullet();
    }
    //iterate through enemies and check if bullet collides with any of them
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(enemies[i][j] != NULL && PCBullet != NULL && check_collision(PCBullet->getRect(), enemies[i][j]->getRect()))
            {
                enemies[i][j]->setIsAlive(false);
                PCBullet->~pcBullet();
                PCBullet = NULL;
                points_ = points_ + enemies[i][j]->score_;
            }
        }
    }
    
    
    if(EBullet != NULL && check_collision(EBullet->getRect(), myPC.getRect()))
    {
        set_next_state(STATE_GAME_OVER);
    }
    
    //every 0.5 seconds move the array of enemies
    if(SDL_GetTicks() - timer > 500)
    {
        timer = SDL_GetTicks();
        
        //if enemy is dead remove them from array
        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if(enemies[i][j] != NULL && !enemies[i][j]->getIsAlive())
                {
                    enemies[i][j]->~Enemy();
                    enemies[i][j] = NULL;
                }
            }
        }
        
        //if enemy exists, move it
        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if(enemies[i][j] != NULL)
                {
                    enemies[i][j]->move();
                }
            }
        }
        
        //updates the rect for enemies which helps decide the direction to move in
        updateEnemyBox();
        
        //increment frame
        frame++;
    }
    
    //move pc
    myPC.move();
    
    //if bullet exists, move it
    if(PCBullet != NULL)
        PCBullet->move();
    
    //if enemy bullet exists, move it
    if(EBullet != NULL)
        EBullet->move();
    
    //if bullet is out of bounds delete it
    if(PCBullet != NULL && PCBullet->outOfBounds())
    {
        PCBullet->~pcBullet();
        PCBullet = NULL;
    }
    
    if(EBullet != NULL && EBullet->outOfBounds())
    {
        EBullet->~enemyBullet();
        EBullet = NULL;
    }
    
    //update the direction of the enemy array
    updateDirection();
}

void MainGame::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    
    //render enemies
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(enemies[i][j] != NULL)
            {
                if(enemies[i][j]->getIsAlive())
                    enemies[i][j]->render(frame % 2);
                else
                    enemies[i][j]->render(2);
            }
        }
    }
    
    //render pc
    myPC.render();
    
    //render pc bullet
    if(PCBullet != NULL)
        PCBullet->render();
    
    if(EBullet != NULL)
        EBullet->render();
    
    score_->render(500, 0);
    
    std::string s = std::to_string(points_);
    
    value_->setString(s);
    
    value_->render(590, 0);
    
    SDL_RenderPresent(renderer);
}

GameOver::GameOver()
{
    SDL_Color white = {255, 255, 255};
    gameOver_ = new Text("Game Over", white, 28);
    playAgain_ = new Text("Play Again", white, 20);
    mainMenu_ = new Text("Main Menu", white, 20);
}
GameOver::~GameOver() {}

void GameOver::handleEvents()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            set_next_state(STATE_EXIT);
            return;
        }
        if(playAgain_->handleEvent())
        {
            set_next_state(STATE_MAIN_GAME);
            return;
        }
        mainMenu_->handleEvent();

    }
}

void GameOver::logic()
{
    /*if(SDL_GetTicks() - timer > 2000)
    {
        set_next_state(STATE_EXIT);
    }*/
}

void GameOver::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    
    SDL_Rect outline = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    SDL_Rect fill = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    
    //render enemies
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(enemies[i][j] != NULL)
            {
                if(enemies[i][j]->getIsAlive())
                    enemies[i][j]->render(frame % 2);
                else
                    enemies[i][j]->render(2);
            }
        }
    }
    
    //render pc
    myPC.render();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fill);
    
    SDL_SetRenderDrawColor(renderer, 57, 255, 20, 255);
    SDL_RenderDrawRect(renderer, &outline);
    
    gameOver_->render((SCREEN_WIDTH - gameOver_->getWidth()) / 2, SCREEN_HEIGHT / 3);
    
    playAgain_->render((SCREEN_WIDTH - playAgain_->getWidth()) / 2, (SCREEN_HEIGHT - playAgain_->getHeight()) / 2);
    
    mainMenu_->render((SCREEN_WIDTH - mainMenu_->getWidth()) / 2, 260);
    
    SDL_RenderPresent(renderer);
    
    
}
