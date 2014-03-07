#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>
#include "../text.h"
#include "otages.h"
#include "scroll.h"
#include "helico.h"
#include "decor.h"
#include "collision.h"
#include "enemi.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void game_loop(SDL_Surface *screen, FMOD_SYSTEM *musicController,int choix);
void free_all(MissileEn me[],MissileHeli ms[],Background *bg,Helico *hl,BaseEn bs[],Enemi en[],Otage ot[]);
int game_over(int armorHeli,int score,SDL_Surface *screen);
int win(Otage ot[],int score,SDL_Surface *screen);
#endif // GAME_H_INCLUDED
