#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "jeu.c"
#include "import.h"


int main(int argc, char *argv[])
{
    SDL_Surface *titre = NULL, *jouer = NULL, *options = NULL, *credits = NULL, *highscore = NULL, *fond = NULL, *texteMenu = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *policeTitre = NULL, *policeMenu = NULL, *policeInfo = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}, couleurRouge = {255, 0, 0};
    int continuer = 1;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Oiram Sorb Beta", NULL);

    fond = IMG_Load("./img/menu/fond.png");
    
    /* Chargement des polices */
    policeTitre = TTF_OpenFont("./fonts/smbfont.ttf", 100);
    policeMenu = TTF_OpenFont("./fonts/emulogic.ttf",20);
    policeInfo = TTF_OpenFont("./fonts/caviardreams.ttf",15);
    
    /* Écriture du texte en mode Blended*/
    titre = TTF_RenderText_Blended(policeTitre, "New Super Oiram Sorb", couleurNoire);
    jouer = TTF_RenderText_Blended(policeMenu, "Nouvelle partie", couleurNoire);
    options = TTF_RenderText_Blended(policeMenu, "Options", couleurNoire);
    credits = TTF_RenderText_Blended(policeMenu, "Credits", couleurNoire);
    highscore = TTF_RenderText_Blended(policeMenu, "Highscore 000000", couleurBlanche);
/*    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music* musique;
    musique = Mix_LoadMUS("./sons/mario-bros-song.mp3");
    Mix_PlayMusic(musique, -1);
    */
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
		  continuer = 0;
		  break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym==SDLK_ESCAPE){
			continuer = 0;
			break;
		}
            case SDL_MOUSEBUTTONDOWN:
		  if(event.button.x >= 350  && event.button.x <= (350+jouer->w) && event.button.y >= 248 && event.button.y <= (248+jouer->h)){
            compteur = 0;
			playGame(1, 1, 1);
			event.button.x += 20;
			event.button.y += 20;
		  }
            case SDL_MOUSEMOTION:
                if(event.motion.x >= 350  && event.motion.x <= (350+jouer->w) && event.motion.y >= 248 && event.motion.y <= (248+jouer->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Nouvelle Partie",couleurRouge);
                        position.x = (LARGEUR_FENETRE / 2) - (jouer->w / 2);
                        position.y = (HAUTEUR_FENETRE / 2) - 2*jouer->h;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour lancer le jeu", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        SDL_Flip(screen);
                        SDL_Delay(5);
                    }
                if(event.motion.x >= 330  && event.motion.x <= (330+options->w) && event.motion.y >= 298 && event.motion.y <= (298+options->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Options",couleurRouge);
                        position.x = 330;
                        position.y = 298;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour modifier vos options", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        SDL_Flip(screen);
                        SDL_Delay(5);
                    }
                if(event.motion.x >= 330  && event.motion.x <= (330+credits->w) && event.motion.y >= 348 && event.motion.y <= (348+credits->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Credits",couleurRouge);
                        position.x = 330;
                        position.y = 348;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */
                        texteMenu = TTF_RenderText_Blended(policeInfo,"2018 - DUFOUR 'Zolkovic' Christophe - BEN SAID 'Thundder' Walid", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        SDL_Flip(screen);
                        SDL_Delay(5);
                    }
        }      

        
        
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, screen, &position); /* Blit du fond */

        position.x = (LARGEUR_FENETRE / 2) - (titre->w / 2);
        position.y = 50;
        SDL_BlitSurface(titre, NULL, screen, &position); /* Blit du titre */
        
        position.x = (LARGEUR_FENETRE / 2) - (jouer->w / 2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*jouer->h;
        SDL_BlitSurface(jouer, NULL, screen, &position); /* Blit de Jouer */
        
        position.x = (LARGEUR_FENETRE / 2) - (options->w / 2);
        position.y += 50;
        SDL_BlitSurface(options, NULL, screen, &position); /* Blit de Options*/
        
        position.x = (LARGEUR_FENETRE / 2) - (credits->w / 2);
        position.y += 50;
        SDL_BlitSurface(credits, NULL, screen, &position); /* Blit de Crédits */
        
        position.x = position.x = (LARGEUR_FENETRE / 2) - (highscore->w / 2);
        position.y += 100;
        SDL_BlitSurface(highscore, NULL, screen, &position); /* Blit du record */
        
        SDL_Flip(screen);
    }

    TTF_CloseFont(policeTitre);
    TTF_CloseFont(policeMenu);
    TTF_CloseFont(policeInfo);
    TTF_Quit();
/*    
    Mix_FreeMusic(musique); 
    Mix_CloseAudio();
    */
    SDL_FreeSurface(titre);
    SDL_FreeSurface(jouer);
    SDL_FreeSurface(options);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(highscore);
    SDL_Quit();

    return EXIT_SUCCESS;
}
