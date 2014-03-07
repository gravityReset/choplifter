#include "game.h"

void game_loop(SDL_Surface *screen, FMOD_SYSTEM *musicController,int choix)
{
    int i;
    int score=0,nbEnemisTue=0,nbBaseDe=0;
    Otage otages[48];
    init_otages(otages);
    Enemi enemis[NBENEMIS];
    init_enemi(enemis);
    int lastEnemi=SDL_GetTicks(),lastBg=-60;
    MissileEn missilesEn[NBMISSILE];
    init_missile_enemis(missilesEn);
    //font

    Text nb_inHeli,nb_sauver;


    Background bg=init_background();
    Helico helico=init_helico(choix);
    MissileHeli missileHelico[20];
    BaseEn bases[3];
    init_base_En(bases);
    for(i=0; i<NBMISSILE; i++)
        missileHelico[i]=init_missile_helico();
    SDL_EnableKeyRepeat(0, 0);
    SDL_Event event;
    int goback=1,compteur=0,hostages_save=0;


    int actualTime,previousTime=0,previousTimechange=0,previousTimeFire=0;//variable de temps

    while( goback)
    {
        srand(time(NULL));
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_SPACE:
                if( (actualTime-previousTimechange )>=200)
                {
                    if(helico.dirTire==1)
                        helico.dirTire=0;
                    else
                        helico.dirTire=1;
                    previousTimechange=SDL_GetTicks();
                }
                break;
            case SDLK_ESCAPE:
                goback = 0;

                break;
            case SDLK_RETURN:
                if( (actualTime-previousTimeFire )>=300)
                {
                    fire_missile_helico(missileHelico,helico,compteur,bg);
                    compteur++;
                    if(compteur>=20)
                        compteur=0;
                    previousTimeFire=SDL_GetTicks();
                }
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            goback = 0;
            break;
        }
        //generation des enemis
        generate_enemis(&lastEnemi,&lastBg,enemis,bg);
        fire_missile_enemis(enemis,missilesEn,helico,bg);
        //déplacement de l'hélico
        move_helico(&helico,event,&bg);
        move_missile_helico(missileHelico,bg);
        move_missile_enemis(missilesEn,bg);
        move_enemi(enemis,helico,bg);
        move_otages(otages, helico,bg,&hostages_save);
        //verif collision
        verif_destruction_baseEn(bases,missileHelico,missilesEn,otages,&nbBaseDe);
        verif_otages_morts(missileHelico, missilesEn,otages);
        verif_otages_baseAm(&helico,otages,bg);
        otages_monte_helico(&helico,otages);
        verif_enemis_morts(missileHelico,missilesEn,enemis,&nbEnemisTue);
        colision_enemis_helico(&helico,enemis);
        verif_missilesEn_helico(missilesEn,&helico);
        //blit
        scroll_display_background(screen,&bg);
        display_bases_En(screen,bases,bg);
        display_nb_otages(screen,helico,&nb_inHeli,&nb_sauver,hostages_save);
        display_enemis(screen,enemis,bg);
        display_helico(screen,&helico);
        display_missile_helico(screen,missileHelico);
        display_life(screen,helico);
        display_missile_enemis(screen,missilesEn);
        display_otages(screen,otages,bg);
        //calcule du score
        score=hostages_save*300+helico.otages*50+nbEnemisTue*100+nbBaseDe*400;
        if(goback!=0)
            goback = game_over(helico.armor,score,screen);
        if(goback!=0)
            goback = win(otages,score,screen);


        //finblit
        //verif win


        SDL_Flip(screen);

        //gestion fps
        actualTime = SDL_GetTicks();
        if( (actualTime - previousTime) <= 30)
            SDL_Delay(30 - (actualTime - previousTime));// permet davoir un fps constant de environ 33
        previousTime = actualTime;

    }
    free_all(missilesEn,missileHelico,&bg,&helico,bases,enemis,otages);
}

void free_all(MissileEn me[],MissileHeli ms[],Background *bg,Helico *hl,BaseEn bs[],Enemi en[],Otage ot[])
{
    int i;
    //free missile
    for(i=0;i<NBMISSILE;i++)
    {
        if(me[i].image!=NULL)
            SDL_FreeSurface(me[i].image);
        if(ms[i].image!=NULL)
            SDL_FreeSurface(ms[i].image);
    }
    //free base
    for(i=0;i<3;i++)
    {
        if(bs[i].active!=NULL)
            SDL_FreeSurface(bs[i].active);
    }
    //free otages
    for(i=0; i<16*3; i++)
    {
        if(ot[i].otage_right_0!=NULL)
           SDL_FreeSurface(ot[i].otage_right_0);
        if(ot[i].otage_right_1!=NULL)
           SDL_FreeSurface(ot[i].otage_right_1);
        if(ot[i].otage_left_0!=NULL)
           SDL_FreeSurface(ot[i].otage_left_0);
        if(ot[i].otage_left_1!=NULL)
           SDL_FreeSurface(ot[i].otage_left_1);

    }
    //free enemis
    for(i=0;i<NBENEMIS;i++)
    {
        if(en[i].active!=NULL)
            SDL_FreeSurface(en[i].active);
        if(en[i].bis!=NULL)
            SDL_FreeSurface(en[i].bis);
    }
    //free bg
    if(bg->image.src!=NULL)
        SDL_FreeSurface(bg->image.src);
    //free heli
    if(hl->helicopter_right_0!=NULL)
        SDL_FreeSurface(hl->helicopter_right_0);
    if(hl->helicopter_right_1!=NULL)
        SDL_FreeSurface(hl->helicopter_right_1);
    if(hl->helicopter_left_0!=NULL)
        SDL_FreeSurface(hl->helicopter_left_0);
    if(hl->helicopter_left_1!=NULL)
        SDL_FreeSurface(hl->helicopter_left_1);
}

int game_over(int armorHeli,int score,SDL_Surface *screen )
{
    if(armorHeli<=0)
    {
        //écriture du score dans le fichier
        FILE* fichier=NULL;
        fichier=fopen("sup.score","a");
        if (fichier != NULL)
        {
            rewind(fichier);
            fprintf(fichier,"%d\n",score);
        }
        fclose(fichier);
        //init affichage du score
        TTF_Font* arcade_font = NULL;
        arcade_font=TTF_OpenFont("ARCADECLASSIC.TTF", 20);
        SDL_Color color = {245, 245, 245};
        Text scoreText;
        char s[40];
        sprintf(s,"sc0re  %d",score);
        scoreText.text = s;

        text_init(&scoreText, arcade_font,color);
        scoreText.position.x=WIDTH/2-scoreText.src->w/2;
        scoreText.position.y=HEIGHT/2;

        //init screen game over
        int goon=1;
        SDL_Surface* image=IMG_Load("assets/gameover.png");
        SDL_Rect position;
        position.x=0;
        position.y=0;
        SDL_BlitSurface(image, NULL, screen, &position);
        display_text(&scoreText,screen);
        SDL_Flip(screen);
        SDL_Delay(200);
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
        SDL_FreeSurface(scoreText.src);
        return 0;
    }
    else
        return 1;
}
int win(Otage ot[],int score,SDL_Surface *screen)
{
    int i;
    for(i=0;i<3*16;i++)
    {
        if(ot[i].position.x==0 && ot[i].position.y==0 || ot[i].active!=NULL || ot[i].inHeli==1)
            return 1;
    }

        //écriture du score dans le fichier
        FILE* fichier=NULL;
        fichier=fopen("sup.score","a");
        if (fichier != NULL)
        {
            //rewind(fichier);
            fprintf(fichier,"%d\n",score);
        }
        fclose(fichier);
        //init affichage du score
        TTF_Font* arcade_font = NULL;
        arcade_font=TTF_OpenFont("ARCADECLASSIC.TTF", 20);
        SDL_Color color = {245, 245, 245};
        Text scoreText;
        char s[40];
        sprintf(s,"sc0re  %d",score);
        scoreText.text = s;

        text_init(&scoreText, arcade_font,color);
        scoreText.position.x=WIDTH/2-scoreText.src->w/2;
        scoreText.position.y=HEIGHT/2;

        //init screen game over
        int goon=1;
        SDL_Surface* image=IMG_Load("assets/win.png");
        SDL_Rect position;
        position.x=0;
        position.y=0;
        SDL_BlitSurface(image, NULL, screen, &position);
        display_text(&scoreText,screen);
        SDL_Flip(screen);
        SDL_Delay(200);
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
        SDL_FreeSurface(scoreText.src);
        return 0;
}
