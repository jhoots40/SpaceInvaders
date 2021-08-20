#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "text.h"

class GameState
{
public:
    virtual void handleEvents() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState() {};
};


class MainGame : public GameState
{
public:
    MainGame();
    ~MainGame();
    void handleEvents();
    void logic();
    void render();
private:
    Text *score_;
    Text *value_;
    int points_;
};

class GameOver : public GameState
{
public:
    GameOver();
    ~GameOver();
    void handleEvents();
    void logic();
    void render();
private:
    Text *gameOver_;
    Text *playAgain_;
    Text *mainMenu_;
};

#endif
