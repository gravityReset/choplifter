#include "collision.h"


void verif_destruction_baseEn(BaseEn base[], MissileHeli mh[],MissileEn me[],Otage otg[],int* nbB)
{
    int i,y,nbb= *nbB;
    for(i=0; i<NBMISSILE; i++)
    {
            for(y=0; y<3; y++)
            {
                if(mh[i].image!=NULL)
                if( (mh[i].position.x+mh[i].image->w) >= base[y].position.x && mh[i].position.x<= (base[y].position.x+base[y].active->w) && base[y].active!=base[y].destroie)
                    if( (mh[i].position.y+mh[i].image->h) >= base[y].position.y && mh[i].position.y<= (base[y].position.y+base[y].active->h))
                    {
                        mh[i].position.x=WIDTH+5;
                        base[y].life--;
                        if(base[y].life<1)
                        {
                            base[y].active=base[y].destroie;
                            rescue_otages(base[y],otg,y);
                            nbb++;
                        }
                    }

                if(me[i].image!=NULL)
                if( (me[i].position.x+me[i].image->w) >= base[y].position.x && me[i].position.x<= (base[y].position.x+base[y].active->w) && base[y].active!=base[y].destroie)
                    if( (me[i].position.y+me[i].image->h) >= base[y].position.y && me[i].position.y<= (base[y].position.y+base[y].active->h))
                    {
                        SDL_FreeSurface(me[i].image);
                        me[i].image=NULL;
                        base[y].life--;
                        if(base[y].life<1)
                        {
                            base[y].active=base[y].destroie;
                            rescue_otages(base[y],otg,y);
                            nbb++;
                        }
                    }
            }

        }

    *nbB=nbb;
}

void verif_otages_morts(MissileHeli mh[],MissileEn me[],Otage otg[])
{
    int y,i;
    for(i=0; i<NBMISSILE; i++)
    {

            for(y=0; y<16*3; y++)
            {
                if(otg[y].active!=NULL)
                {
                     if(mh[i].image!=NULL)
                    if( (mh[i].position.x+mh[i].image->w) >= otg[y].position.x && mh[i].position.x<= (otg[y].position.x+otg[y].active->w))
                        if( (mh[i].position.y+mh[i].image->h) >= otg[y].position.y && mh[i].position.y<= (otg[y].position.y+otg[y].active->h))
                        {

                            mh[i].position.x=WIDTH+5;
                            //SDL_FreeSurface(otg[y].active);
                            otg[y].active=NULL;
                            otg[y].inHeli=2;
                        }
                        if(me[i].image!=NULL && otg[y].active!=NULL)
                    if( (me[i].position.x+me[i].image->w) >= otg[y].position.x && me[i].position.x<= (otg[y].position.x+otg[y].active->w))
                        if( (me[i].position.y+me[i].image->h) >= otg[y].position.y && me[i].position.y<= (otg[y].position.y+otg[y].active->h))
                        {
                            SDL_FreeSurface(me[i].image);
                            me[i].image=NULL;
                            //SDL_FreeSurface(otg[y].active);
                            otg[y].active=NULL;
                            otg[y].inHeli=2;
                        }
                }

        }
    }
}

int otages_monte_helico(Helico* hl,Otage otg[])
{
    int i;

    for(i=0; i<16*3; i++)
    {
        if(otg[i].active!=NULL && otg[i].inHeli==0)
            if(hl->otages < 16)
            {
                if(hl->position.x<=otg[i].position.x && (hl->position.x+ hl->active->w)>=otg[i].position.x && hl->position.y>=299 )
                {
                    hl->otages++;
                    //SDL_FreeSurface(otg[i].active);
                    otg[i].active=NULL;
                    otg[i].inHeli=1;
                    return 1;
                }
            }
            else
            {
                return 2;
            }
    }
    return 0;
}

int verif_otages_baseAm(Helico* hl,Otage otg[],Background bg)
{
    if(bg.posX==0 && hl->position.x<=190 && hl->position.y>=299)
    {
        int i;
        for(i=0;i<(16*3);i++)
        {
            if(otg[i].inHeli==1 && otg[i].active==NULL)
            {
                if(hl->otages==1)
                {
                    otg[i].faitcoucou=1;
                    otg[i].img_fait_coucou_0=IMG_Load("assets/otages/otage_coucou_0.png");
                    otg[i].img_fait_coucou_1=IMG_Load("assets/otages/otage_coucou_1.png");
                }

                otg[i].active=otg[i].otage_left_0;
                otg[i].position.x=(hl->position.x+hl->active->w)- (4*(i%16));
                otg[i].position.y=hl->position.y;
                otg[i].bgX=0;
                hl->otages--;
                return 1;
            }
        }
    }
    else
    {
        return 0;
    }
}

//int verif_colision_enemi();
void verif_enemis_morts(MissileHeli mh[],MissileEn me[],Enemi en[],int *nbT)
{
    int y,i,nbt= (*nbT);
    for(i=0; i<20; i++)
    {
            for(y=0; y<NBENEMIS; y++)
            {
                if(en[y].active!=NULL)
                {
                    if(mh[i].image!=NULL )
                    if( (mh[i].position.x+mh[i].image->w) >= en[y].position.x && mh[i].position.x<= (en[y].position.x+en[y].active->w))
                        if( (mh[i].position.y+mh[i].image->h) >= en[y].position.y && mh[i].position.y<= (en[y].position.y+en[y].active->h))
                        {
                            mh[i].position.x=WIDTH+5;
                            nbt++;
                            SDL_FreeSurface(en[y].active);
                            en[y].active=NULL;
                            en[y].type=INCONU;

                        }
                    if(me[i].image!=NULL && en[y].active!=NULL)
                    if( (me[i].position.x+me[i].image->w) >= en[y].position.x && me[i].position.x<= (en[y].position.x+en[y].active->w))
                        if( (me[i].position.y+me[i].image->h) >= en[y].position.y && me[i].position.y<= (en[y].position.y+en[y].active->h))
                        {
                            SDL_FreeSurface(me[i].image);
                            me[i].image=NULL;
                            SDL_FreeSurface(en[y].active);
                            en[y].active=NULL;
                            en[y].type=INCONU;

                        }
                }
        }
    }
    *nbT=nbt;
}
void colision_enemis_helico(Helico* hl,Enemi en[])
{
    int i,y;

    for(i=0; i<NBENEMIS; i++)
    {
        if(en[i].active!=NULL)
        {

            if(hl->position.y<=(en[i].position.y+en[i].active->h) && (hl->position.y+ hl->active->h)>=en[i].position.y )
            if(hl->position.x<=(en[i].position.x+en[i].active->w) && (hl->position.x+ hl->active->w)>=en[i].position.x )
            {
                    SDL_FreeSurface(en[i].active);
                    en[i].active=NULL;
                    en[i].type=INCONU;
                    hl->armor--;
            }
        }
    }
}

void verif_missilesEn_helico(MissileEn me[],Helico* hl)
{
    int i;
    for(i=0;i<NBMISSILE;i++)
        if(me[i].image!=NULL)
        {
            if(hl->position.y<=(me[i].position.y+me[i].image->h) && (hl->position.y+ hl->active->h)>=me[i].position.y )
            if(hl->position.x<=(me[i].position.x+me[i].image->w) && (hl->position.x+ hl->active->w)>=me[i].position.x )
            {
                    SDL_FreeSurface(me[i].image);
                    me[i].image=NULL;
                    hl->armor--;
            }
        }
}

