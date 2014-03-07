#ifndef DECOR_H_INCLUDED
#define DECOR_H_INCLUDED
#include "../image.h"
#include "../definitions.h"
#include "scroll.h"

#include <SDL/SDL.h>
struct BaseEn
{
    int life;
    int bgX;
    SDL_Surface* active;
    SDL_Surface* destroie;
    SDL_Rect position;
};
typedef struct BaseEn BaseEn;
void init_base_En(BaseEn bases[]);
void display_bases_En(SDL_Surface* screen,BaseEn bases[], Background bg);
#endif // DECOR_H_INCLUDED
