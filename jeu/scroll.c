#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>

#include "../image.h"
#include "scroll.h"

void scroll_display_background(SDL_Surface *screen,Background* backg )
{
    backg->image.position.x=backg->posX;
    display_image( &backg->image, screen);
}
Background init_background()
{
    Background bg;
    bg.image.src=IMG_Load("assets/background/background.png");
    bg.image.position.x=0;
    bg.image.position.y=0;
    bg.posX=0;
    return bg;
}
void move_background(Background* backg,int speed)
{
    if(backg->posX+speed<=0 && (backg->posX+speed) > -1800)
        backg->posX+=speed;
   // else
       // backg->posX=0;
}
