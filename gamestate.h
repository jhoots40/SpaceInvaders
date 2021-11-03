#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "text.h"
#include "defense.h"
#include <vector>

class GameState
{
public:
    virtual void handleEvents() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState() {};
};

class MainMenu : public GameState
{
public:
    MainMenu();
    ~MainMenu();
    void handleEvents();
    void logic();
    void render();
private:
    Text *spaceInvaders_;
    Text *play_;
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
    int points_;
    std::vector<Defense *> d1;
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
