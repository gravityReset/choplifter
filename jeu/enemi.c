#include "enemi.h"
#include "../definitions.h"
#include <math.h>

void init_enemi(Enemi enemi[])
{
    int i;

    for(i=0; i<NBENEMIS; i++)
    {
        enemi[i].type=INCONU;
        enemi[i].active= NULL;
        enemi[i].bis=NULL;
        enemi[i].bgX=0;
        enemi[i].dir=RIGHT;
    }

}

void move_enemi(Enemi en[],Helico hl,Background bg)
{
    int y;
    for(y=0; y<NBENEMIS; y++)
    {

        if(en[y].active!=NULL)
        {
            switch(en[y].type)
            {
            case SOUCOUPE:
                if(en[y].position.x<(hl.position.x+hl.active->w/2))
                {
                    en[y].position.x++;
                }
                else if(en[y].position.x>(hl.position.x+hl.active->w/2))
                {
                    en[y].position.x--;
                }
                if(en[y].position.y<(hl.position.y+hl.active->h/2))
                {
                    en[y].position.y++;
                }
                else if(en[y].position.y>(hl.position.y+hl.active->h/2))
                {
                    en[y].position.y--;
                }
                break;
            case TANK:
                if( (en[y].position.x+en[y].active->w/2+ DSTTIR ) <= (hl.position.x+hl.active->w/2) )
                {
                    en[y].position.x++;
                }
                else if( (en[y].position.x+en[y].active->w/2 - DSTTIR) > (hl.position.x+hl.active->w/2) || (en[y].position.x+en[y].active->w > WIDTH) )
                {
                    en[y].position.x--;
                }
                break;
            case AVION:
                if(en[y].dir==RIGHT)
                {
                    if(LIMITE_GAUCHE<en[y].position.x)
                        en[y].position.x--;
                    else
                        en[y].dir=LEFT;
                }
                else
                {
                    if(LIMITE_DROITE>en[y].position.x)
                        en[y].position.x++;
                    else
                        en[y].dir=RIGHT;
                }
                break;
            default:
                break;
            }
        }//fin du if !NULL
    }//fin du for

}

void display_enemis(SDL_Surface* screen,Enemi en[],Background bg)
{
    int y;

    for(y=0; y<NBENEMIS; y++)
    {
        if(en[y].active!=NULL)
        {

            en[y].position.x=en[y].position.x-(en[y].bgX- bg.posX);

            en[y].bgX=bg.posX;
            SDL_BlitSurface((en[y].dir==0) ? en[y].active :en[y].bis, NULL, screen, &en[y].position);
        }
    }
}

void generate_enemis(int *lastEnemi,int *lastBg,Enemi en[],Background bg)
{
    int i=0;
        //( abs( (*lastBg) - bg.posX ) >50 )&&
    if(  (*lastEnemi)+1000<SDL_GetTicks())
    {
        while(en[i].active!=NULL && i<20)
        {
            i++;
        }
        if((rand()%5)==0 && i<20)
        {
            switch( (rand()%3)+1)
            {
            case SOUCOUPE:
                en[i].active=IMG_Load("assets/enemis/soucoupe.png");
                en[i].bis=NULL;
                en[i].type=SOUCOUPE;
                en[i].bgX=bg.posX;
                en[i].position.y=0;
                en[i].position.x=WIDTH*(rand()%2);
                en[i].dir=0;
                break;
            case TANK:
                en[i].active=IMG_Load("assets/enemis/tank.png");
                en[i].bis=NULL;
                en[i].type=TANK;
                en[i].bgX=bg.posX;
                en[i].position.y=HEIGHT-30-(rand()%50);
                en[i].position.x=WIDTH;
                en[i].dir=0;
                break;

            case AVION:
                en[i].active=IMG_Load("assets/enemis/avion1.png");
                en[i].bis=IMG_Load("assets/enemis/avion.png");
                en[i].type=AVION;
                en[i].bgX=bg.posX;
                en[i].position.y=50+(rand()%50);
                en[i].position.x=WIDTH;
                en[i].dir=1;
                break;
            }
            en[i].lastshot=SDL_GetTicks()-3000;
            *lastBg=bg.posX;
            *lastEnemi=SDL_GetTicks();

        }
    }

}

//missile
void init_missile_enemis(MissileEn me[])
{
    int i;
    for(i=0; i<NBMISSILE; i++)
    {
        me[i].speedX=0;
        me[i].speedY=0;
        me[i].image=NULL;
        me[i].position.x=0;
        me[i].position.y=0;
    }
}

void display_missile_enemis(SDL_Surface *screen, MissileEn me[])
{
    int i;

    for(i=0; i<NBMISSILE; i++)
    {
        if(me[i].image!=NULL)
            SDL_BlitSurface(me[i].image, NULL, screen, &me[i].position);
    }
}

void move_missile_enemis(MissileEn me[],Background bg)
{
    int i;
    for(i=0; i<NBMISSILE; i++)
    {
        if( (me[i].position.x<=1 || me[i].position.x>=WIDTH || me[i].position.y<=1 || me[i].position.y>=HEIGHT) && me[i].image!=NULL )
        {
            SDL_FreeSurface(me[i].image);
            me[i].image=NULL;

        }

        if(me[i].image!=NULL)
        {
            me[i].position.x+=round(me[i].speedX *2) +(bg.posX-me[i].bgX);
            me[i].bgX=bg.posX;
            me[i].position.y+=round(me[i].speedY *2);
        }
    }
}

void fire_missile_enemis(Enemi en[], MissileEn me[], Helico hl, Background bg)
{
    int i,j=0,dstX,dstY,pX=hl.position.x,pY=hl.position.y;

    for(i=0; i<NBENEMIS; i++)
    {
        if(en[i].active!=NULL && ( en[i].type==TANK || en[i].type==AVION ) && en[i].lastshot+1000 < SDL_GetTicks())
        {
            if( (rand()%4)==1 )
            {
                j=0;
                while(me[j].image!=NULL && j<NBMISSILE){j++;}
                if(NBMISSILE>j)
                {
                    en[i].lastshot=SDL_GetTicks();
                    me[j].position.x=en[i].position.x+(en[i].active->w/2);
                    me[j].position.y=en[i].position.y -10 + ( (en[i].type==AVION)? en[i].active->h+11 : 0);
                    me[j].image= IMG_Load("assets/enemis/missile.png");
                    me[j].bgX=bg.posX;
                    dstX=abs(me[j].position.x-pX);
                    dstY=abs(me[j].position.y-pY);

                    if(dstX>dstY)
                    {
                        me[j].speedX=(pX<me[j].position.x)? -1: 1;
                        me[j].speedY=(double)(me[j].position.y-pY)/(double)(me[j].position.x-pX);
                        if(en[i].type==AVION && me[j].speedY<0)
                            me[j].speedY=0;

                    }
                    else
                    {
                        me[j].speedY=(pY<me[j].position.y)? -1: 1;
                        me[j].speedX=- (double)(me[j].position.x-pX)/(double)(me[j].position.y-pY);
                        if(en[i].type==TANK && me[j].speedY>0)
                            me[j].speedY=0;

                    }
                }
            }
        }
    }
}



