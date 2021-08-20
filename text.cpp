#include "text.h"
#include "globals.h"
#include "functions.h"
#include "constants.h"

Text::Text(std::string s, SDL_Color color, int size) : s_(s)
{
    font_ = TTF_OpenFont("space_invaders.ttf", size);
    if(font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        throw std::runtime_error("Failed to load font");
    }
    
    //SDL_DestroyTexture(textTexture_);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font_, s.c_str(), color);
    if(textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        textTexture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture_ == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            box_.w = textSurface->w;
            box_.h = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
}

Text::~Text()
{
    SDL_DestroyTexture(textTexture_);
    textTexture_ = NULL;
    
    TTF_CloseFont(font_);
    font_ = NULL;
}

void Text::render(int x, int y)
{
    box_.x = x;
    box_.y = y;
    SDL_RenderCopy(renderer, textTexture_, NULL, &box_);

}

void Text::setColor(SDL_Color c)
{
    if(textTexture_ != NULL)
    {
        SDL_DestroyTexture(textTexture_);
        textTexture_ = NULL;
    }
    
    SDL_Surface *textSurface = TTF_RenderText_Solid(font_, s_.c_str(), c);
    if(textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        textTexture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture_ == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        
        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
}

bool Text::handleEvent()
{
    if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        bool inside = true;
        
        if(x < box_.x)
        {
            inside = false;
        }
        if(x > box_.x + box_.w)
        {
            inside = false;
        }
        if(y < box_.y)
        {
            inside = false;
        }
        if(y > box_.y + box_.h)
        {
            inside = false;
        }
        
        if(!inside)
        {
            SDL_Color white = {255, 255, 255};
            this->setColor(white);
        }
        else
        {
            SDL_Color green = {57, 255, 20};
            this->setColor(green);
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                return true;
            }
        }
    }
    return false;
}

void Text::setString(std::string s)
{
    if(textTexture_ != NULL)
    {
        SDL_DestroyTexture(textTexture_);
        textTexture_ = NULL;
    }
    
    SDL_Color c = {255, 255, 255};
    
    SDL_Surface *textSurface = TTF_RenderText_Solid(font_, s.c_str(), c);
    if(textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        textTexture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture_ == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            box_.w = textSurface->w;
            box_.h = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
}
