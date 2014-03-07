#include "score.h"

void score_board(SDL_Surface *screen)
{

        //écriture du score dans le fichier
        FILE* fichier=NULL;
        char score[15][10]={'0'};
        int i=0;
        fichier=fopen("sup.score","r");
        if (fichier != NULL)
        {

            while (i<15)
            {
                if(fgets(score[i], 10, fichier) == NULL )
                    score[i][0]='0';
            i++;
            }
        }

        fclose(fichier);
        //init affichage du score
        TTF_Font* arcade_font = NULL;
        arcade_font=TTF_OpenFont("ARCADECLASSIC.TTF", 20);
        SDL_Color color = {20, 20, 20};
        Text scoreText[15];
        for(i=0;i<15;i++)
        {
            if(score[i][0]!='0')
                score[i][strlen(score[i])-1] =0;
            scoreText[i].text = score[i];
            text_init(&scoreText[i], arcade_font,color);
            scoreText[i].position.x=WIDTH/2-scoreText[i].src->w/2;
            scoreText[i].position.y=i*22+50;
        }


        //init screen game over
        int goon=1;
        SDL_Surface* image=IMG_Load("assets/score.png");
        SDL_Rect position;
        position.x=0;
        position.y=0;
        SDL_BlitSurface(image, NULL, screen, &position);
        for(i=0;i<15;i++)
        display_text(&scoreText[i],screen);
        SDL_Flip(screen);
        SDL_Delay(2000);
        SDL_Event event;
        while(goon)
        {
            SDL_WaitEvent(&event);
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    goon=0;
                break;
                default:
                    break;
                }
        }
        TTF_CloseFont(arcade_font);
        SDL_FreeSurface(image);
        for(i=0;i<15;i++)
        SDL_FreeSurface(scoreText[i].src);

}

