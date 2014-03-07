#ifndef HELICO_H_INCLUDED
#define HELICO_H_INCLUDED
#include <SDL/SDL.h>
#include "../text.h"
#include "../definitions.h"
struct Helico
{
    int speed;
    int armor;
    int dir;
    int dirTire;
    int compteur;
    int otages;
    SDL_Surface* active;
    SDL_Surface* helicopter_right_0;
    SDL_Surface* helicopter_right_1;
    SDL_Surface* helicopter_left_0;
    SDL_Surface* helicopter_left_1;
    SDL_Rect position;
};
typedef struct Helico Helico;
struct MissileHeli
{
    int speedX;
    int speedY;
    int bgX;
    SDL_Surface* image;
    SDL_Rect position;
};
typedef struct MissileHeli MissileHeli;

Helico init_helico(int choix);
void display_helico(SDL_Surface *screen,Helico* hl);
void move_helico(Helico* hl,SDL_Event event,Background* backg);
void display_life(SDL_Surface *screen,Helico hl);
void display_nb_otages(SDL_Surface *screen,Helico hl,Text* nbo,Text* nbs,int nb_sauver);
//missile
MissileHeli init_missile_helico();
void display_missile_helico(SDL_Surface *screen, MissileHeli mh[]);
void move_missile_helico(MissileHeli mh[],Background bg);
void fire_missile_helico(MissileHeli mh[], Helico hl, int compteurMissile,Background bg);

#endif // HELICO_H_INCLUDED
