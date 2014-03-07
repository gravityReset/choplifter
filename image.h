#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifndef IMAGE_H
#define IMAGE_H
struct Image
{
    SDL_Surface *src;
    SDL_Rect position;
};
typedef struct Image Image;
void image_init(Image *image);
void display_image(Image *image, SDL_Surface *screen);
void fade_in(SDL_Surface *screen);
void fade_out(SDL_Surface *screen);
#endif