#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct Text Text;
struct Text
{
    SDL_Surface *src;
    SDL_Rect position;
    float x;
    float y;
    char *text;
    int top;
    int opacity;
};
void text_init(Text *text, TTF_Font *font, SDL_Color color);
void display_text(Text *text, SDL_Surface *screen);
#endif
