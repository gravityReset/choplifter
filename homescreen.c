#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <SDL/SDL_ttf.h>

#include "definitions.h"
#include "homescreen.h"
#include "text.h"

void display_background(Image *background, SDL_Surface *screen)
{
    SDL_BlitSurface(background->src, NULL, screen, &background->position);
}

void homescreen_loop(SDL_Surface *screen, int *go_on, FMOD_SYSTEM *musicController)
{
    // Resources
    Image logo = {IMG_Load("logo.png")};
    image_init(&logo);
    Image background = {IMG_Load("background.png")};
    image_init(&background);
    SDL_Surface *helicopter_1 = IMG_Load("assets/helicopter/helicopter_right_green_1.png");
    SDL_Surface *helicopter_0 = IMG_Load("assets/helicopter/helicopter_right_green_0.png");
    Image helicopter = {helicopter_1};
    image_init(&helicopter);
    int helicopter_ = 0;


    // Fonts
    TTF_Font *arcade_font = NULL;
    arcade_font = TTF_OpenFont("ARCADECLASSIC.TTF", 35);
    SDL_Color blackColor = {51, 51, 51};
    Text startGame;
    startGame.text = "Press  Enter  to  Start";
    text_init(&startGame, arcade_font, blackColor);
    startGame.position.y = HEIGHT - startGame.src->h - 10;
    int startGameShow = 1;

    // Main return
    int homescreen = 1;

    // Timers
    int previousTime = 0, actualTime = 0;
    int startGameTime = 0;
    int helicopterTime = 0;

    // Delay
    int delay;

    // Logo position
    int logoTop = 0;

    // Sound
    FMOD_SOUND *backgroundMusic;
    FMOD_RESULT backgroundMusicResult;

    backgroundMusicResult = FMOD_System_CreateSound(musicController, "sounds/background_music_1.wav", FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL, 0, &backgroundMusic);

    if (backgroundMusicResult != FMOD_OK) {
        fprintf(stderr, "Could not load audio file sounds/background_music_1.wav\n");
        exit(EXIT_FAILURE);
    }

    FMOD_Sound_SetLoopCount(backgroundMusic, -1);

    FMOD_System_PlaySound(musicController, FMOD_CHANNEL_FREE, backgroundMusic, 0, NULL);

    SDL_Event event;
    while(go_on || homescreen)
    {
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_RETURN:
                        homescreen = 0;
                        break;
                    case SDLK_ESCAPE:
                        homescreen = 0;
                        break;
                    default:
                        break;
                }
            case SDL_QUIT:
                go_on = 0;
                break;
        }

        actualTime = SDL_GetTicks();
        if (actualTime - previousTime > 30)
        {
            delay = actualTime - previousTime;
            display_image(&background, screen);
            if (!logoTop) {
                if (logo.position.y > 10) {
                    logo.position.y -= 1 * (float) delay / 10;
                }
                else {
                    logoTop = 1;
                }
            }
            display_image(&logo, screen);
            if (logoTop && startGameShow) {
                display_text(&startGame, screen);
            }
            display_image(&helicopter, screen);
            previousTime = actualTime;
        }
        else if(actualTime - helicopterTime > 60) {
            switch (helicopter_) {
                case 0:
                    helicopter.src = helicopter_0;
                    helicopter_ = 1;
                    break;
                case 1:
                    helicopter.src = helicopter_1;
                    helicopter_ = 0;
                    break;
            }
            helicopterTime = actualTime;
        }
        else if(actualTime - startGameTime > 625) {
            startGameShow = !startGameShow;
            startGameTime = actualTime;
        }
        else
        {
            SDL_Delay(30 - (actualTime - previousTime));
        }

        SDL_Flip(screen);
    }

    FMOD_Sound_Release(backgroundMusic);
    return;
}
