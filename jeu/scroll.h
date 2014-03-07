#ifndef SCROLL_H_INCLUDED
#define SCROLL_H_INCLUDED
#include "../image.h"
struct Background
{
    int posX;
    Image image;
};
typedef struct Background Background;

void scroll_display_background(SDL_Surface *screen,Background* backg );
Background init_background();
void move_background(Background* backg,int speed);
#endif // SCROLL_H_INCLUDED
