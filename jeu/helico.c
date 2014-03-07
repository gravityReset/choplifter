#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>
#include "scroll.h"
#include "helico.h"

Helico init_helico(int choix)
{
    Helico hl;
    switch(choix)
        {
        case 1:

            hl.speed=3;
            hl.armor=2;
            hl.active= IMG_Load("assets/helicopter/helicopter_right_green_0.png");
            hl.helicopter_right_0= IMG_Load("assets/helicopter/helicopter_right_green_0.png");
            hl.helicopter_right_1= IMG_Load("assets/helicopter/helicopter_right_green_1.png");
            hl.helicopter_left_0= IMG_Load("assets/helicopter/helicopter_left_green_0.png");
            hl.helicopter_left_1= IMG_Load("assets/helicopter/helicopter_left_green_1.png");
            break;
        case 2:
            hl.speed=4;
            hl.armor=1;
            hl.active= IMG_Load("assets/helicopter/helicopter_right_red_0.png");
            hl.helicopter_right_0= IMG_Load("assets/helicopter/helicopter_right_red_0.png");
            hl.helicopter_right_1= IMG_Load("assets/helicopter/helicopter_right_red_1.png");
            hl.helicopter_left_0= IMG_Load("assets/helicopter/helicopter_left_red_0.png");
            hl.helicopter_left_1= IMG_Load("assets/helicopter/helicopter_left_red_1.png");
            break;
        case 3:
            hl.speed=2;
            hl.armor=3;
            hl.active= IMG_Load("assets/helicopter/helicopter_right_blue_0.png");
            hl.helicopter_right_0= IMG_Load("assets/helicopter/helicopter_right_blue_0.png");
            hl.helicopter_right_1= IMG_Load("assets/helicopter/helicopter_right_blue_1.png");
            hl.helicopter_left_0= IMG_Load("assets/helicopter/helicopter_left_blue_0.png");
            hl.helicopter_left_1= IMG_Load("assets/helicopter/helicopter_left_blue_1.png");
            break;
        default:
            hl.speed=3;
            hl.armor=2;
            hl.active= IMG_Load("assets/helicopter/helicopter_right_green_0.png");
            hl.helicopter_right_0= IMG_Load("assets/helicopter/helicopter_right_green_0.png");
            hl.helicopter_right_1= IMG_Load("assets/helicopter/helicopter_right_green_1.png");
            hl.helicopter_left_0= IMG_Load("assets/helicopter/helicopter_left_green_0.png");
            hl.helicopter_left_1= IMG_Load("assets/helicopter/helicopter_left_green_1.png");
            break;
        }
    hl.dirTire=0;
    hl.dir=RIGHT;
    hl.position.x=LIMITE_GAUCHE;
    hl.position.y=LIMITE_BAS-hl.active->h;
    hl.otages=0;
    return hl;

}
void display_helico(SDL_Surface *screen,Helico* hl)
{
    if(hl->dir == LEFT)
        {
            if(hl->compteur< VITESSE_HELICE)
                hl->active = hl->helicopter_left_0;
            else if(hl->compteur>= VITESSE_HELICE)
                {
                    hl->active = hl->helicopter_left_1;
                    if(hl->compteur>VITESSE_HELICE*2)
                        hl->compteur=0;
                }
        }
    else
        {
            if(hl->compteur<VITESSE_HELICE)
                hl->active = hl->helicopter_right_0;
            else if(hl->compteur>=VITESSE_HELICE)
                {
                    hl->active = hl->helicopter_right_1;
                    if(hl->compteur>VITESSE_HELICE*2 )
                        hl->compteur=0;
                }
        }
    hl->compteur++;
    SDL_BlitSurface(hl->active, NULL, screen, &hl->position);
}

void move_helico(Helico* hl,SDL_Event event,Background* backg)
{
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if(keystates[SDLK_DOWN])
        {
            if((hl->position.y+hl->active->h)<LIMITE_BAS)
                hl->position.y+=hl->speed;
        }
    if(keystates[SDLK_UP])
        {
            if((hl->position.y)>LIMITE_HAUT)
                hl->position.y-=hl->speed;

        }
    if(keystates[SDLK_RIGHT])
        {
            if((hl->position.x+hl->active->w)<LIMITE_DROITE)
                hl->position.x+=hl->speed;
            else
                move_background(backg, -hl->speed);
            hl->dir=RIGHT;
        }
    if(keystates[SDLK_LEFT])
        {
            if((hl->position.x)>LIMITE_GAUCHE)
                hl->position.x-=hl->speed;
            else
                move_background(backg,hl->speed);
            hl->dir=LEFT;
        }

}
//MissileHeli
MissileHeli init_missile_helico()
{
    MissileHeli mh;
    mh.speedX=0;
    mh.speedY=0;
    mh.image=NULL;
    mh.position.x=0;
    mh.position.y=0;
    return mh;
}

void display_missile_helico(SDL_Surface *screen, MissileHeli* mh)
{
    int i,n = 20;

    for(i=0;i<n;i++)
    {
        if(mh[i].image!=NULL)
            SDL_BlitSurface(mh[i].image, NULL, screen, &mh[i].position);
    }
}
void move_missile_helico(MissileHeli mh[],Background bg)
{
    int i,n = 20;
    for(i=0;i<n;i++)
    {
        if( (mh[i].position.x<=0 || mh[i].position.x>=WIDTH || mh[i].position.y<=1 || mh[i].position.y>=HEIGHT) && mh[i].image!=NULL )
        {
            SDL_FreeSurface(mh[i].image);
            mh[i].image=NULL;
        }

        if(mh[i].image!=NULL)
        {
            mh[i].position.x+=mh[i].speedX *5 +(bg.posX-mh[i].bgX);
            mh[i].bgX=bg.posX;
            mh[i].position.y+=mh[i].speedY *5;
        }
    }
}
void fire_missile_helico(MissileHeli* mh, Helico hl, int compteurMissile, Background bg)
{
    int n=(compteurMissile % 20);
    mh[n].position.x=hl.position.x+(hl.active->w/2);
    mh[n].position.y=hl.position.y+hl.active->h;
    mh[n].image= IMG_Load("assets/helicopter/missile.png");
    mh[n].bgX=bg.posX;
    if(hl.dirTire==1)
    {
        mh[n].speedX=0;
        mh[n].speedY=1;
    }
    else
    {
        if(hl.dir==RIGHT)
            mh[n].speedX=1;
        else
            mh[n].speedX=-1;

        mh[n].speedY=0;
    }

}
void display_life(SDL_Surface *screen,Helico hl)
{
    int i;
    SDL_Surface* img = IMG_Load("assets/coeur.png");
    SDL_Rect pos;
    pos.y=4;
    pos.x=-18;
    for(i=0;i<hl.armor;i++)
    {
        pos.x+=18+4;
        SDL_BlitSurface(img, NULL, screen, &pos);
    }
}
void display_nb_otages(SDL_Surface *screen,Helico hl,Text* nbo,Text* nbs,int nb_sauver)
{
    TTF_Font *arcade_font_20 = NULL;
    arcade_font_20 = TTF_OpenFont("ARCADECLASSIC.TTF", 20);
    SDL_Color blackColor = {0, 0, 0};
    char str[80];
    sprintf(str, "%d hostages in the heli", hl.otages);

    nbo->text = str;

    text_init(nbo, arcade_font_20, blackColor);
    sprintf(str, "%d hostage save",nb_sauver );
    nbs->text = str;
    text_init(nbs, arcade_font_20, blackColor);
    nbo->position.y= 4;
    nbo->position.x= 120;
    nbs->position.y= 4;
    nbs->position.x= 400;
    display_text(nbo, screen);
    display_text(nbs, screen);
}
