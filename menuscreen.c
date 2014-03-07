#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "score.h"
#include "text.h"
#include "definitions.h"
#include "menuscreen.h"
#ifndef IMAGE_H
    #include "image.h"
#endif



void menuscreen_down(Image *arrow, int *arrow_status)
{
    if (*arrow_status < 3) {
        arrow->position.y += 50;
        *arrow_status += 1;
    }
}

void menuscreen_up(Image *arrow, int *arrow_status)
{
    if (*arrow_status > 1) {
        arrow->position.y -= 50;
        *arrow_status -= 1;
    }
}


void menuscreen_loop(SDL_Surface *screen, int *go_on, FMOD_SYSTEM *musicController)
{

    SDL_EnableKeyRepeat(0, 0);
    // Resources
    Image logo = {IMG_Load("logo.png")};
    image_init(&logo);
    logo.position.y = 10;
    Image background = {IMG_Load("background.png")};
    image_init(&background);
    int fade = 0;

    SDL_Surface *black_surface;
    black_surface = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, 250, 200, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
    SDL_FillRect(black_surface, NULL, 0);
    SDL_SetAlpha(black_surface, SDL_SRCALPHA, (Uint8)(128));
    SDL_Rect blackSurfacePosition;
    blackSurfacePosition.y = HEIGHT / 2 - black_surface->h / 2 + 50;
    blackSurfacePosition.x = WIDTH / 2 - black_surface->w / 2 + 100;

    // Main return
    int menuScreen = 1;

    // Timers
    int previousTime = 0, actualTime = 0;

    // Delay
    int delay;

    // Return Menu loops
    int returnSelect = 0;

    // Arrow
    Image arrow = {IMG_Load("assets/arrow_right_16x16_white.png")};
    image_init(&arrow);
    arrow.position.x += 10;
    int arrow_status = 1;

    // Sound
    FMOD_SOUND *backgroundMusic;
    FMOD_RESULT backgroundMusicResult;

    // Font
    TTF_Font *arcade_font = NULL;
    arcade_font = TTF_OpenFont("ARCADECLASSIC.TTF", 30);
    SDL_Color whiteColor = {245, 245, 245};
    Text startGame, scoreBoard, howToPlay;
    startGame.text = "Start Game";
    text_init(&startGame, arcade_font, whiteColor);
    startGame.position.x += 100;
    scoreBoard.text = "Scoreboard";
    text_init(&scoreBoard, arcade_font, whiteColor);
    scoreBoard.position.x += 100;
    scoreBoard.position.y += 50;
    howToPlay.text = "How to Play";
    text_init(&howToPlay, arcade_font, whiteColor);
    howToPlay.position.x += 100;
    howToPlay.position.y += 100;

    backgroundMusicResult = FMOD_System_CreateSound(musicController, "sounds/background_music_2.mp3", FMOD_CREATESAMPLE, 0, &backgroundMusic);

    if (backgroundMusicResult != FMOD_OK) {
        fprintf(stderr, "Could not load audio file sounds/background_music_2.mp3\n");
        exit(EXIT_FAILURE);
    }

    FMOD_Sound_SetLoopCount(backgroundMusic, -1);

    FMOD_System_PlaySound(musicController, FMOD_CHANNEL_FREE | FMOD_LOOP_NORMAL, backgroundMusic, 0, NULL);

    display_image(&background, screen);

    SDL_Event event;
    while(go_on || menuScreen)
    {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_DOWN:
                        menuscreen_down(&arrow, &arrow_status);
                        break;
                    case SDLK_UP:
                        menuscreen_up(&arrow, &arrow_status);
                        break;
                    case SDLK_ESCAPE:
                        menuScreen = 0;
                        go_on = 0;
                        break;
                    case SDLK_RETURN:
                        if (arrow_status == 1) {
                            returnSelect = select_menu_loop(screen, musicController);
                        }
                        else if(arrow_status == 2)
                            score_board(screen);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                go_on = 0;
                break;
        }

        actualTime = SDL_GetTicks();
        if (actualTime - previousTime > 30)
        {
            delay = actualTime - previousTime;
            display_image(&background, screen);
            display_image(&logo, screen);
            SDL_BlitSurface(black_surface, NULL, screen, &blackSurfacePosition);
            display_image(&arrow, screen);
            switch (arrow_status) {
                case 1:
                    startGame.position.x += 15;
                    display_text(&startGame, screen);
                    display_text(&scoreBoard, screen);
                    display_text(&howToPlay, screen);
                    startGame.position.x -= 15;
                    break;
                case 2:
                    scoreBoard.position.x += 15;
                    display_text(&startGame, screen);
                    display_text(&scoreBoard, screen);
                    display_text(&howToPlay, screen);
                    scoreBoard.position.x -= 15;
                    break;
                case 3:
                    howToPlay.position.x += 15;
                    display_text(&startGame, screen);
                    display_text(&scoreBoard, screen);
                    display_text(&howToPlay, screen);
                    howToPlay.position.x -= 15;
                    break;
            }
            previousTime = actualTime;
        }
        else
        {
            SDL_Delay(30 - (actualTime - previousTime));
        }

        if (!fade) {
            fade_out(screen);
            fade = 1;
        }

        SDL_Flip(screen);

    }

    TTF_CloseFont(arcade_font);
    return;
}

int select_menu_loop(SDL_Surface *screen, FMOD_SYSTEM *musicController)
{
    SDL_EnableKeyRepeat(0, 0);
    // Resources
    Image logo = {IMG_Load("logo.png")};
    image_init(&logo);
    logo.position.y = 10;
    Image background = {IMG_Load("background.png")};
    Image trgLeft = {IMG_Load("assets/select_left.png")};
    Image trgRight = {IMG_Load("assets/select_right.png")};
    image_init(&trgLeft);
    image_init(&trgRight);
    trgRight.position.x = WIDTH - 220 - (trgRight.src->w / 2);
    trgLeft.position.x = 150 + (trgLeft.src->w / 2);
    int trgRight_ = 1;
    int trgLeft_ = 0;

    // Text
    TTF_Font *arcade_font_24 = NULL;
    TTF_Font *arcade_font_20 = NULL;
    arcade_font_24 = TTF_OpenFont("ARCADECLASSIC.TTF", 24);
    arcade_font_20 = TTF_OpenFont("ARCADECLASSIC.TTF", 20);
    SDL_Color whiteColor = {245, 245, 245};
    Text fennec, hummingBird, dauphin, armor, speed;
    fennec.text = "AS550 Fennec";
    hummingBird.text = "EC120B HummingBird";
    dauphin.text = "AS365 Dauphin";
    armor.text = "Armor";
    speed.text = "Speed";
    text_init(&fennec, arcade_font_24, whiteColor);
    text_init(&hummingBird, arcade_font_24, whiteColor);
    text_init(&dauphin, arcade_font_24, whiteColor);
    text_init(&armor, arcade_font_20, whiteColor);
    text_init(&speed, arcade_font_20, whiteColor);
    fennec.position.y+= 60;
    hummingBird.position.y+= 60;
    dauphin.position.y+= 60;
    armor.position.y+= 100;
    armor.position.x-= 70;
    speed.position.y+= 140;
    speed.position.x-= 70;

    image_init(&background);

    // Helicopters
    SDL_Surface *helicopter_green_0 = IMG_Load("assets/helicopter/helicopter_right_green_0.png");
    SDL_Surface *helicopter_red_0 = IMG_Load("assets/helicopter/helicopter_right_red_0.png");
    SDL_Surface *helicopter_blue_0 = IMG_Load("assets/helicopter/helicopter_right_blue_0.png");
    Image helicopter = {helicopter_green_0};
    image_init(&helicopter);
    int helicopter_ = 1;

    // Stars
    SDL_Surface *one_of_3 = IMG_Load("assets/1_of_3.png");
    SDL_Surface *two_of_3 = IMG_Load("assets/2_of_3.png");
    SDL_Surface *three_of_3 = IMG_Load("assets/3_of_3.png");
    Image armor_stars = {two_of_3};
    image_init(&armor_stars);
    armor_stars.position.y+= 100;
    armor_stars.position.x+= 30;
    Image speed_stars = {two_of_3};
    image_init(&speed_stars);
    speed_stars.position.y+= 140;
    speed_stars.position.x+= 30;

    // Overlay
    SDL_Surface *black_surface;
    black_surface = SDL_CreateRGBSurface(screen->flags|SDL_SRCALPHA, 325, 134, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
    SDL_FillRect(black_surface, NULL, 0);
    SDL_SetAlpha(black_surface, SDL_SRCALPHA, (Uint8)(128));
    SDL_Rect blackSurfacePosition;
    blackSurfacePosition.y = HEIGHT / 2 - black_surface->h / 2 + 110;
    blackSurfacePosition.x = WIDTH / 2 - black_surface->w / 2;

    // Main return
    int selectScreen = 1;

    // Timers
    int previousTime = 0, actualTime = 0;

    // Delay
    int delay;

    // Sound
    FMOD_SOUND *backgroundMusic;
    FMOD_RESULT backgroundMusicResult;

    FMOD_Sound_SetLoopCount(backgroundMusic, -1);
    backgroundMusicResult = FMOD_System_CreateSound(musicController, "sounds/background_music_2.mp3", FMOD_CREATESAMPLE, 0, &backgroundMusic);

    if (backgroundMusicResult != FMOD_OK) {
        fprintf(stderr, "Could not load audio file sounds/background_music_2.mp3\n");
        exit(EXIT_FAILURE);
    }

    display_image(&background, screen);

    SDL_Event event;
    while(selectScreen == 1)
    {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_RETURN:
                        game_loop(screen,musicController,helicopter_);
                        SDL_EnableKeyRepeat(0, 0);
                        break;
                    case SDLK_ESCAPE:
                        selectScreen = 0;

                        break;
                    case SDLK_LEFT:
                        switch (helicopter_) {
                            case 1:
                                trgLeft_ = 0;
                                break;
                            case 2:
                                helicopter.src = helicopter_green_0;
                                helicopter_ = 1;
                                trgLeft_ = 0;
                                break;
                            case 3:
                                helicopter.src = helicopter_red_0;
                                helicopter_ = 2;
                                trgLeft_ = 1;
                                trgRight_ = 1;
                                break;
                        }
                        break;
                    case SDLK_RIGHT:
                        switch (helicopter_) {
                            case 1:
                                helicopter.src = helicopter_red_0;
                                helicopter_ = 2;
                                trgLeft_ = 1;
                                break;
                            case 2:
                                helicopter.src = helicopter_blue_0;
                                helicopter_ = 3;
                                trgRight_ = 0;
                                break;
                            case 3:
                                trgRight_ = 0;
                                break;
                        }
                        break;
                    default:
                        selectScreen = 1;
                        break;
                }
                break;
            case SDL_QUIT:
                selectScreen = 0;
                break;
        }

        actualTime = SDL_GetTicks();
        if (actualTime - previousTime > 30)
        {
            delay = actualTime - previousTime;
            display_image(&background, screen);
            if (trgLeft_)
                display_image(&trgLeft, screen);
            if (trgRight_)
                display_image(&trgRight, screen);
            display_image(&logo, screen);
            display_image(&helicopter, screen);
            SDL_BlitSurface(black_surface, NULL, screen, &blackSurfacePosition);
            switch (helicopter_) {
                case 1:
                    display_text(&fennec, screen);
                    armor_stars.src = two_of_3;
                    speed_stars.src = two_of_3;
                    display_image(&armor_stars, screen);
                    display_image(&speed_stars, screen);
                    break;
                case 2:
                    display_text(&hummingBird, screen);
                    armor_stars.src = one_of_3;
                    speed_stars.src = three_of_3;
                    display_image(&armor_stars, screen);
                    display_image(&speed_stars, screen);
                    break;
                case 3:
                    display_text(&dauphin, screen);
                    armor_stars.src = three_of_3;
                    speed_stars.src = one_of_3;
                    display_image(&armor_stars, screen);
                    display_image(&speed_stars, screen);
                    break;
            }
            display_text(&armor, screen);
            display_text(&speed, screen);
            previousTime = actualTime;
        }
        else
        {
            SDL_Delay(30 - (actualTime - previousTime));
        }
        SDL_Flip(screen);
    }

    TTF_CloseFont(arcade_font_24);
    TTF_CloseFont(arcade_font_20);
    return selectScreen;
}
