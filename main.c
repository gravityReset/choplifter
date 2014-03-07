#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>

#include "definitions.h"
#include "homescreen.h"
#include "menuscreen.h"

int main (int argc, char** argv)
{
    // Variables
    int go_on = 1;

    // Screen
    SDL_Surface *screen = NULL;

    // Initialization
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
        fprintf(stderr, "SDL initialization error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1) {
        fprintf(stderr, "TTF initilization error : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Video mode
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_ShowCursor(SDL_DISABLE);

    if (screen == NULL) {
        fprintf(stderr, "Could not load video mode : %s\n", SDL_GetError());
    }

    // Sound

    FMOD_SYSTEM *sound;
    FMOD_System_Create(&sound);
    FMOD_System_Init(sound, 1, FMOD_INIT_NORMAL, NULL);

    // Caption

    SDL_WM_SetCaption("SupCopter 2013", NULL);

    // Key repeat
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);


    // Home screen loop
    homescreen_loop(screen, &go_on, sound);

    fade_in(screen);

    menuscreen_loop(screen, &go_on, sound);

    FMOD_System_Close(sound);
    FMOD_System_Release(sound);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
