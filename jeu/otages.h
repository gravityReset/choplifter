#ifndef OTAGES_H_INCLUDED
#define OTAGES_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>
#include "scroll.h"
#include "decor.h"
#include "helico.h"
struct Otage
{
    int bgX;
    int compteur;
    int dir;
    int inHeli;
    int faitcoucou;
    SDL_Surface* active;
    SDL_Surface* otage_right_0;
    SDL_Surface* otage_right_1;
    SDL_Surface* otage_left_0;
    SDL_Surface* otage_left_1;
    SDL_Surface* img_fait_coucou_0;
    SDL_Surface* img_fait_coucou_1;
    SDL_Rect position;
};
typedef struct Otage Otage;

void init_otages(Otage otg[]);
void display_otages(SDL_Surface* screen,Otage otg[],Background bg);
void move_otages(Otage otg[],Helico hl,Background bg,int* otageS);

void rescue_otages(BaseEn bs,Otage otg[],int nb_base);
#endif // OTAGES_H_INCLUDED
