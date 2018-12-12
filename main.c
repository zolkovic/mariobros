#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "jeu.c"
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL,*temps = NULL, *titre = NULL, *jouer = NULL, *options = NULL, *credits = NULL, *highscore = NULL, *fond = NULL, *chrono = NULL, *texteMenu = NULL;
    SDL_Rect position, positionClic;
    SDL_Event event;
    TTF_Font *policeTitre = NULL, *policeMenu = NULL, *policeInfo = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}, couleurRouge = {255, 0, 0};
    int continuer = 1;
    int tempsActuel = 0, tempsPrecedent = 0, compteur = 0;
    char time[10] = "";
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Test Menu", NULL);

    fond = IMG_Load("./img/menu/fond.png");
    chrono = IMG_Load("./img/menu/xchrono.png");
    /* Chargement des polices */
    policeTitre = TTF_OpenFont("./fonts/smbfont.ttf", 100);
    policeMenu = TTF_OpenFont("./fonts/emulogic.ttf",20);
    policeInfo = TTF_OpenFont("./fonts/caviardreams.ttf",15);
    
      /* Initialisation du temps et du texte */
    tempsActuel = SDL_GetTicks();
    sprintf(time, "%d", compteur);
    
    /* Écriture du texte en mode Solid*/
    temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche);
    /* Écriture du texte en mode Blended*/
    titre = TTF_RenderText_Blended(policeTitre, "New Super Mega Mario Bros", couleurNoire);
    jouer = TTF_RenderText_Blended(policeMenu, "Jouer", couleurNoire);
    options = TTF_RenderText_Blended(policeMenu, "Options", couleurNoire);
    credits = TTF_RenderText_Blended(policeMenu, "Credits", couleurNoire);
    highscore = TTF_RenderText_Blended(policeMenu, "Highscore 000000", couleurBlanche);
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x >= 350  && event.button.x <= (350+jouer->w) && event.button.y >= 248 && event.button.y <= (248+jouer->h)){
                    playGame();
                }
            case SDL_MOUSEMOTION:
                if(event.motion.x >= 350  && event.motion.x <= (350+jouer->w) && event.motion.y >= 248 && event.motion.y <= (248+jouer->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Jouer",couleurRouge);
                        position.x = 350;
                        position.y = 248;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour lancer le jeu", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */ 
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                if(event.motion.x >= 330  && event.motion.x <= (330+options->w) && event.motion.y >= 298 && event.motion.y <= (298+options->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Options",couleurRouge);
                        position.x = 330;
                        position.y = 298;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour modifier vos options", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */ 
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
                if(event.motion.x >= 330  && event.motion.x <= (330+credits->w) && event.motion.y >= 348 && event.motion.y <= (348+credits->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Credits",couleurRouge);
                        position.x = 330;
                        position.y = 348;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */
                        texteMenu = TTF_RenderText_Blended(policeInfo,"2018\nDUFOUR 'Zolkovic' Christophe - BEN SAID 'Thundder' Walid", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, ecran, &position); /* Blit du texte */ 
                        SDL_Flip(ecran);
                        SDL_Delay(100);
                    }
        }      

        //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >= 1000) /* Si 1000 ms au moins se sont écoulées */
        {
            compteur += 1; /* On rajoute 1s au compteur */
            sprintf(time, "%d", compteur); /* On écrit dans la chaîne "temps" le nouveau temps */
            SDL_FreeSurface(temps); /* On supprime la surface précédente */
            temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surface */
            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
        }

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */
        
        position.x = LARGEUR_FENETRE - temps->w - 5;
        position.y = temps->h - 20;
        SDL_BlitSurface(temps, NULL, ecran, &position); /* Blit du temps*/
        
        position.x -= 20;
        SDL_BlitSurface(chrono, NULL, ecran, &position); /* Blit du chronomètre */

        position.x = (LARGEUR_FENETRE / 2) - (titre->w / 2);
        position.y = 50;
        SDL_BlitSurface(titre, NULL, ecran, &position); /* Blit du titre */
        
        position.x = (LARGEUR_FENETRE / 2) - (jouer->w / 2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*jouer->h;
        SDL_BlitSurface(jouer, NULL, ecran, &position); /* Blit de Jouer */
        
        position.x = (LARGEUR_FENETRE / 2) - (options->w / 2);
        position.y += 50;
        SDL_BlitSurface(options, NULL, ecran, &position); /* Blit de Options*/
        
        position.x = (LARGEUR_FENETRE / 2) - (credits->w / 2);
        position.y += 50;
        SDL_BlitSurface(credits, NULL, ecran, &position); /* Blit de Crédits */
        
        position.x = position.x = (LARGEUR_FENETRE / 2) - (highscore->w / 2);
        position.y += 100;
        SDL_BlitSurface(highscore, NULL, ecran, &position); /* Blit du record */
        
        SDL_Flip(ecran);
    }

    TTF_CloseFont(policeTitre);
    TTF_CloseFont(policeMenu);
    TTF_CloseFont(policeInfo);
    TTF_Quit();

    SDL_FreeSurface(titre);
    SDL_FreeSurface(jouer);
    SDL_FreeSurface(options);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(highscore);
    SDL_Quit();

    return EXIT_SUCCESS;
}
