#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>

#include "image.h"

void homescreen_loop(SDL_Surface *screen, int *go_on, FMOD_SYSTEM *musicController);

void logo_init(Image *logo);
void logo_move_up(Image *logo, Uint32 delay);
void logo_move_down(Image *logo, Uint32 delay);
