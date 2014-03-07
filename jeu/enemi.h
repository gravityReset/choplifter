#ifndef ENEMI_H_INCLUDED
#define ENEMI_H_INCLUDED
#define INCONU 0
#define TANK 1
#define SOUCOUPE 2
#define AVION 3
#define NBENEMIS 20
#define DSTTIR 75
#include <SDL/SDL.h>
#include "decor.h"
#include "scroll.h"
#include "helico.h"
#include "../definitions.h"
#include <stdlib.h>
#include <time.h>

struct Enemi
{
    int type;
    int bgX;
    int dir;
    int lastshot;
    int posX;
    SDL_Surface* active;
    SDL_Surface* bis;
    SDL_Rect position;
};
typedef struct Enemi Enemi;
struct MissileEn
{
    double speedX;
    double speedY;
    int bgX;
    SDL_Surface* image;
    SDL_Rect position;
};
typedef struct MissileEn MissileEn;
void init_enemi(Enemi enemi[]);
void move_enemi(Enemi en[],Helico hl,Background bg);
void display_enemis(SDL_Surface* screen,Enemi en[],Background bg);
void generate_enemis(int *lastEnemi,int *lastBg,Enemi en[],Background bg);
//missiles enemis
void init_missile_enemis(MissileEn ms[]);
void display_missile_enemis(SDL_Surface *screen, MissileEn me[]);
void move_missile_enemis(MissileEn me[],Background bg);
void fire_missile_enemis(Enemi en[], MissileEn me[], Helico hl, Background bg);

#endif // ENEMI_H_INCLUDED
