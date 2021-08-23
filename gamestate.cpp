#include "gamestate.h"
#include "globals.h"
#include "functions.h"
#include "constants.h"
#include "text.h"

MainMenu::MainMenu()
{
    SDL_Color white = {255, 255, 255};
    spaceInvaders_ = new Text("Space Invaders", white, 35);
    play_ = new Text("Click here to play!", white, 28);
}

MainMenu::~MainMenu()
{
    if(spaceInvaders_ != NULL)
    {
        delete spaceInvaders_;
        spaceInvaders_ = NULL;
    }
    if(play_ != NULL)
    {
        delete play_;
        play_ = NULL;
    }
}

void MainMenu::handleEvents()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            set_next_state(STATE_EXIT);
            return;
        }
        if(play_->handleEvent())
        {
            set_next_state(STATE_MAIN_GAME);
            return;
        }
    }
}

void MainMenu::logic()
{
    
}

void MainMenu::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    
    spaceInvaders_->render((SCREEN_WIDTH - spaceInvaders_->getWidth()) / 2, SCREEN_HEIGHT / 3);
    
    play_->render((SCREEN_WIDTH - play_->getWidth()) / 2, (SCREEN_HEIGHT - play_->getHeight()) / 2);

    SDL_RenderPresent(renderer);
}

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
    
    if(def.size() > 0)
    {
        def.clear();
    }
    
    if(score != NULL)
    {
        delete score;
        score = NULL;
    }
    
    if(value != NULL)
    {
        delete value;
        value = NULL;
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
    score = new Text("Score: ", white, 20);
    value = new Text("0", white, 20);
    
    def.push_back(new Defense(104, 360));
    def.push_back(new Defense(104, 372));
    def.push_back(new Defense(104, 384));
    def.push_back(new Defense(116, 360));
    def.push_back(new Defense(116, 372));
    def.push_back(new Defense(128, 360));
    def.push_back(new Defense(128, 372));
    def.push_back(new Defense(140, 360));
    def.push_back(new Defense(140, 372));
    def.push_back(new Defense(140, 384));
    
    def.push_back(new Defense(232, 360));
    def.push_back(new Defense(232, 372));
    def.push_back(new Defense(232, 384));
    def.push_back(new Defense(244, 360));
    def.push_back(new Defense(244, 372));
    def.push_back(new Defense(256, 360));
    def.push_back(new Defense(256, 372));
    def.push_back(new Defense(268, 360));
    def.push_back(new Defense(268, 372));
    def.push_back(new Defense(268, 384));
    
    def.push_back(new Defense(360, 360));
    def.push_back(new Defense(360, 372));
    def.push_back(new Defense(360, 384));
    def.push_back(new Defense(372, 360));
    def.push_back(new Defense(372, 372));
    def.push_back(new Defense(384, 360));
    def.push_back(new Defense(384, 372));
    def.push_back(new Defense(396, 360));
    def.push_back(new Defense(396, 372));
    def.push_back(new Defense(396, 384));
    
    def.push_back(new Defense(488, 360));
    def.push_back(new Defense(488, 372));
    def.push_back(new Defense(488, 384));
    def.push_back(new Defense(500, 360));
    def.push_back(new Defense(500, 372));
    def.push_back(new Defense(512, 360));
    def.push_back(new Defense(512, 372));
    def.push_back(new Defense(524, 360));
    def.push_back(new Defense(524, 372));
    def.push_back(new Defense(524, 384));
    
    
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
    
    for(int i = 0; i < def.size(); i++)
    {
        if(PCBullet != NULL && check_collision(PCBullet->getRect(), def[i]->getRect()))
        {
            PCBullet->~pcBullet();
            PCBullet = NULL;
            if(def[i]->health == 0)
                def.erase(def.begin() + i);
            else
                --def[i]->health;
        }
    }
    
    for(int i = 0; i < def.size(); i++)
    {
        if(EBullet != NULL && check_collision(EBullet->getRect(), def[i]->getRect()))
        {
            EBullet->~enemyBullet();
            EBullet = NULL;
            if(def[i]->health == 0)
                def.erase(def.begin() + i);
            else
                --def[i]->health;
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
        
        //update the direction of the enemy array
        updateDirection();
        
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
    
    score->render(500, 0);
    
    std::string s = std::to_string(points_);
    
    value->setString(s);
    
    value->render(590, 0);
    
    for(int i = 0; i < def.size(); i++)
    {
        def[i]->render();
    }
    
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
        if(mainMenu_->handleEvent())
        {
            set_next_state(STATE_MAIN_MENU);
        }

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
    
    for(int i = 0; i < def.size(); i++)
    {
        def[i]->render();
    }
    
    score->render(500, 0);

    value->render(590, 0);
    
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
