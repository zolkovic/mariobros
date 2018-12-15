#include "jeu.c"
#include "options.c"
#include "import.h"


int main(int argc, char *argv[])
{
    SDL_Surface *titre, *new, *load, *options, *credits, *highscore, *fond, *texteMenu;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *policeTitre, *policeMenu, *policeInfo;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255}, couleurRouge = {255, 0, 0};
    int continuer = 1;
    
    SDL_Init(SDL_INIT_EVERYTHING);
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
    new = TTF_RenderText_Blended(policeMenu, "Nouvelle partie", couleurNoire);
    load = TTF_RenderText_Blended(policeMenu, "Charger partie", couleurNoire);
    options = TTF_RenderText_Blended(policeMenu, "Options", couleurNoire);
    credits = TTF_RenderText_Blended(policeMenu, "Credits", couleurNoire);
    
    Mix_Chunk *son;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(10);
    son = Mix_LoadWAV("./sons/hurry-up.wav");
    Mix_PlayChannel(1, son, 0);
    highscore = read_highscore(highscore, policeMenu, couleurBlanche);
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
		  continuer = 0;
		  highscore = read_highscore(highscore, policeMenu, couleurBlanche);
		  break;
	    case SDL_KEYDOWN:
		if (event.key.keysym.sym==SDLK_ESCAPE){
			continuer = 0;
			highscore = read_highscore(highscore, policeMenu, couleurBlanche);
			break;
		}
            case SDL_MOUSEBUTTONDOWN:
		if(event.button.x >= 252  && event.button.x <= (252+new->w) && event.button.y >= 204 && event.button.y <= (204+new->h)){
			if (me !=1 && me != 2)
				Options(&me);
			compteur = 300;
			monde = 1;
            level = 1;
			respawnX = SPAWN_X; //6000 SPAWN_X
			respawnY = SPAWN_Y; //200 SPAWN_Y
			vie = 3;
			score = 0;
			playGame(me, monde, level, &compteur, vie, respawnX, respawnY, &score);
			event.button.x = 0;
			event.button.y = 0;
		  } 
		  else if(event.button.x >= 262  && event.button.x <= (262+load->w) && event.button.y >= 253 && event.button.y <= (253+load->h) && compteur != 0){
			playGame(me, monde, level, &compteur, vie, respawnX, respawnY, &score);
			event.button.x = 0;
			event.button.y = 0;
		  } 
		  else if(event.motion.x >= 330  && event.motion.x <= (330+options->w) && event.motion.y >= 298 && event.motion.y <= (298+options->h)){
			Options(&me);
			event.button.x = 0;
			event.button.y = 0;
		  }
            case SDL_MOUSEMOTION:
                if(event.motion.x >= 252  && event.motion.x <= (252+new->w) && event.motion.y >= 204 && event.motion.y <= (204+new->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Nouvelle Partie",couleurRouge);
			position.x = (LARGEUR_FENETRE / 2) - (new->w / 2);
			position.y = (HAUTEUR_FENETRE / 2) - 2*new->h - 50;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour lancer une nouvelle partie", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                    }
                else if(event.motion.x >= 330  && event.motion.x <= (330+options->w) && event.motion.y >= 298 && event.motion.y <= (298+options->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Options",couleurRouge);
                        position.x = 330;
                        position.y = 298;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                        texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour modifier vos options", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                    }
                else if(event.motion.x >= 330  && event.motion.x <= (330+credits->w) && event.motion.y >= 348 && event.motion.y <= (348+credits->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Credits",couleurRouge);
                        position.x = 330;
                        position.y = 348;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */
                        texteMenu = TTF_RenderText_Blended(policeInfo,"2018 - DUFOUR 'Zolkovic' Christophe - BEN SAID 'Thundder' Walid", couleurNoire);
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                    }
                else if(event.motion.x >= 262  && event.motion.x <= (262+load->w) && event.motion.y >= 253 && event.motion.y <= (253+load->h))
                    {
                        texteMenu = TTF_RenderText_Blended(policeMenu,"Charger Partie",couleurRouge);
                        position.x = (LARGEUR_FENETRE / 2) - (load->w / 2);
                        position.y = (HAUTEUR_FENETRE / 2) - 2*load->h;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
			if (compteur != 0){
				texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour reprendre l'ancienne partie", couleurNoire);
			}else{
				texteMenu = TTF_RenderText_Blended(policeInfo,"Aucune sauvegarde existante !", couleurNoire);
			}
                        position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
                        position.y = HAUTEUR_FENETRE - 200;
                        SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
                    }
                    SDL_Flip(screen);
        }      

        
        
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, screen, &position); /* Blit du fond */

        position.x = (LARGEUR_FENETRE / 2) - (titre->w / 2);
        position.y = 50;
        SDL_BlitSurface(titre, NULL, screen, &position); /* Blit du titre */
        
        position.x = (LARGEUR_FENETRE / 2) - (new->w / 2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*new->h - 50;
        SDL_BlitSurface(new, NULL, screen, &position); /* Blit de Nouvelle Partie */
	
        position.x = (LARGEUR_FENETRE / 2) - (load->w / 2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*load->h;
        SDL_BlitSurface(load, NULL, screen, &position); /* Blit de Charger Partie */
        
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
    
    Mix_FreeChunk(son); 
    Mix_CloseAudio();
    
    SDL_FreeSurface(titre);
    SDL_FreeSurface(new);
    SDL_FreeSurface(options);
    SDL_FreeSurface(credits);
    SDL_FreeSurface(highscore);
    SDL_Quit();

    return EXIT_SUCCESS;
}
