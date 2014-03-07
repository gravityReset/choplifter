#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>


#ifndef IMAGE_H
    #include "image.h"
#endif
void menuscreen_loop(SDL_Surface *screen, int *go_on, FMOD_SYSTEM *musicController);
void menuscreen_up(Image *arrow, int *arrow_status);
void menuscreen_down(Image *arrow, int *arrow_status);
int select_menu_loop(SDL_Surface *screen, FMOD_SYSTEM *musicController);

