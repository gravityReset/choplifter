#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "definitions.h"
#ifndef IMAGE_H
    #include "image.h"
#endif

void image_init(Image *image)
{
    image->position.x = (WIDTH / 2) - (image->src->w / 2);
    image->position.y = (HEIGHT / 2) - (image->src->h / 2);
}

void display_image(Image *image, SDL_Surface *screen)
{
    SDL_BlitSurface(image->src, NULL, screen, &image->position);
}

// http://www.archivum.info/sdl@libsdl.org/2006-01/00075/Re-(SDL)-SDL-video-and-fading-the-screen.html
void fade_in(SDL_Surface *screen)
{
    float alpha_inc = 256 / 10;
    float alpha = 255;

    SDL_Surface *screen_copy, *black_surface;

    screen_copy = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if (screen_copy == NULL) {
        fprintf(stderr, "Could not copy screen : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_BlitSurface(screen, NULL, screen_copy, NULL);

    black_surface = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if (black_surface == NULL) {
        fprintf(stderr, "Could not create black surface : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(black_surface, NULL, 0);

    while (alpha > 0) {
        SDL_SetAlpha(black_surface, SDL_SRCALPHA, (Uint8)(255 - alpha));

        SDL_BlitSurface(screen_copy, NULL, screen, NULL);
        SDL_BlitSurface(black_surface, NULL, screen, NULL);

        SDL_Flip(screen);
        SDL_Delay(30);
        alpha -= alpha_inc;
    }
}

void fade_out(SDL_Surface *screen)
{
    float alpha_inc = 256 / 10;
    float alpha = 0;

    SDL_Surface *screen_copy, *black_surface;

    screen_copy = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if (screen_copy == NULL) {
        fprintf(stderr, "Could not copy screen : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_BlitSurface(screen, NULL, screen_copy, NULL);

    black_surface = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    if (black_surface == NULL) {
        fprintf(stderr, "Could not create black surface : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(black_surface, NULL, 0);

    while (alpha <= 255) {
        SDL_SetAlpha(black_surface, SDL_SRCALPHA, (Uint8)(255 - alpha));

        SDL_BlitSurface(screen_copy, NULL, screen, NULL);
        SDL_BlitSurface(black_surface, NULL, screen, NULL);

        SDL_Flip(screen);
        SDL_Delay(30);
        alpha += alpha_inc;
    }
}
