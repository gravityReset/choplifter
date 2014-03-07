#include "decor.h"
#include "scroll.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


init_base_En(BaseEn bases[])
{
    int i,dst;
    for(i=0;i<3;i++)
    {
        bases[i].life=4;
        bases[i].position.y=HEIGHT-100;
        bases[i].position.x=(i+1)*WIDTH;
        bases[i].bgX=(i+1)*WIDTH;
        bases[i].active=IMG_Load("assets/background/base.png");
        bases[i].destroie=IMG_Load("assets/background/base_d.png");
    }
}

display_bases_En(SDL_Surface* screen,BaseEn bases[], Background bg)
{
    int i;
    for(i=0;i<3;i++)
    {
        bases[i].position.x=bases[i].bgX+ bg.posX;
        SDL_BlitSurface(bases[i].active, NULL, screen, &bases[i].position);
    }
}
