#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "definitions.h"
#include "text.h"

void text_init(Text *text, TTF_Font *font, SDL_Color color)
{
    text->src = TTF_RenderText_Blended(font, text->text, color);
    text->position.x = (WIDTH / 2) - (text->src->w / 2);
    text->x = (WIDTH / 2) - (text->src->w / 2);
    text->position.y = (HEIGHT / 2) - (text->src->h / 2);
    text->y = (HEIGHT / 2) - (text->src->h / 2);
}

void display_text(Text *text, SDL_Surface *screen)
{
    SDL_BlitSurface(text->src, NULL, screen, &text->position);
}
