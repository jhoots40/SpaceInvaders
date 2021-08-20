#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text
{
public:
    Text(std::string s, SDL_Color color, int size);
    ~Text();
    void render(int x, int y);
    void setColor(SDL_Color c);
    void setString(std::string s);
    int getWidth() {return box_.w;}
    int getHeight() {return box_.h;}
    bool handleEvent();
private:
    TTF_Font *font_;
    SDL_Texture *textTexture_;
    std::string s_;
    SDL_Rect box_;
};

#endif
