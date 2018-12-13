#include "import.h"

void Options(int *me){
	SDL_Surface *titre, *personnage, *mario, *luigi, *fond, *ok, *texte;
	SDL_Rect position;
	SDL_Event event;
	TTF_Font *police, *policeTitre, *policeInfo;
	SDL_Color couleurNoire = {0, 0, 0}, couleurRouge = {255, 0, 0};
	int continuer = 1;

	fond = IMG_Load("./img/menu/fond.png");
	
	/* Chargement des polices */
	policeTitre = TTF_OpenFont("./fonts/smbfont.ttf", 100);
	police = TTF_OpenFont("./fonts/emulogic.ttf",20);
	policeInfo = TTF_OpenFont("./fonts/caviardreams.ttf",15);
	
	/* Écriture du texte en mode Blended*/
	titre = TTF_RenderText_Blended(policeTitre, "New Super Oiram Sorb", couleurNoire);
	personnage = TTF_RenderText_Blended(police, "Perso : ", couleurNoire);
	ok = TTF_RenderText_Blended(police, "[OK]", couleurNoire);
        if (*me == 2){
		    mario = TTF_RenderText_Blended(police, "Mario", couleurNoire);
		    luigi = TTF_RenderText_Blended(police, "Luigi", couleurRouge);
	}else {
		    *me = 1;
		    mario = TTF_RenderText_Blended(police, "Mario", couleurRouge);
		    luigi = TTF_RenderText_Blended(police, "Luigi", couleurNoire);
	}

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
		  if(event.button.x >= 392  && event.button.x <= (392+mario->w) && event.button.y >= 253 && event.button.y <= (253+mario->h)){
			*me = 1;
			mario = TTF_RenderText_Blended(police, "Mario", couleurRouge);
			luigi = TTF_RenderText_Blended(police, "Luigi", couleurNoire);
		  } 
		  else if(event.button.x >= 502  && event.button.x <= (502+luigi->w) && event.button.y >= 253 && event.button.y <= (253+luigi->h)){
			*me = 2;
			mario = TTF_RenderText_Blended(police, "Mario", couleurNoire);
			luigi = TTF_RenderText_Blended(police, "Luigi", couleurRouge);
			
		  } 
		  else if(event.button.x >= 367  && event.button.x <= (367+ok->w) && event.button.y >= 456 && event.button.y <= (456+ok->h)){
			continuer = 0;
		  } 
	    case SDL_MOUSEMOTION:
		  if(event.motion.x >= 392  && event.motion.x <= (392+mario->w) && event.motion.y >= 253 && event.motion.y <= (253+mario->h))
		      {
			  texte = TTF_RenderText_Blended(police,"Mario",couleurRouge);
			  position.x = (LARGEUR_FENETRE / 2) - ((mario->w+luigi->w) / 2) + (personnage->w/2) + 10;
			  position.y = (HAUTEUR_FENETRE / 2) - 2*mario->h;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit de Mario */
			  texte = TTF_RenderText_Blended(policeInfo,"Cliquez pour jouer avec Mario", couleurNoire);
			  position.x = (LARGEUR_FENETRE / 2) - (texte->w / 2);
			  position.y = HAUTEUR_FENETRE - 200;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit du texte */ 
		      }
		  else if(event.motion.x >= 502  && event.motion.x <= (502+luigi->w) && event.motion.y >= 253 && event.motion.y <= (253+luigi->h))
		      {
			  texte = TTF_RenderText_Blended(police,"Luigi",couleurRouge);
			  position.x = (LARGEUR_FENETRE / 2) - (luigi->w / 2) + ((personnage->w + mario->w)/2) + 20;
			  position.y = (HAUTEUR_FENETRE / 2) - 2*luigi->h;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit de Luigi */
			  texte = TTF_RenderText_Blended(policeInfo,"Cliquez pour jouer avec Luigi", couleurNoire);
			  position.x = (LARGEUR_FENETRE / 2) - (texte->w / 2);
			  position.y = HAUTEUR_FENETRE - 200;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit du texte */ 
		      }
		  else if(event.motion.x >= 367  && event.motion.x <= (367+ok->w) && event.motion.y >= 456 && event.motion.y <= (456+ok->h))
		      {
			  texte = TTF_RenderText_Blended(police,"[OK]",couleurRouge);
			  position.x = (LARGEUR_FENETRE / 2) - (ok->w / 2);
			  position.y = HAUTEUR_FENETRE - 150;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit du ok */
			  texte = TTF_RenderText_Blended(policeInfo,"Confirmer les changements", couleurNoire);
			  position.x = (LARGEUR_FENETRE / 2) - (texte->w / 2);
			  position.y = HAUTEUR_FENETRE - 200;
			  SDL_BlitSurface(texte, NULL, screen, &position); /* Blit du texte */ 
		      }
		SDL_Flip(screen);
        }      
        
	  position.x = 0;
	  position.y = 0;
	  SDL_BlitSurface(fond, NULL, screen, &position); /* Blit du fond */

	  position.x = (LARGEUR_FENETRE / 2) - (titre->w / 2);
	  position.y = 50;
	  SDL_BlitSurface(titre, NULL, screen, &position); /* Blit du titre */
	  
	  position.x = (LARGEUR_FENETRE / 2) - ((personnage->w+mario->w+luigi->w) / 2);
	  position.y = (HAUTEUR_FENETRE / 2) - 2*personnage->h;
	  SDL_BlitSurface(personnage, NULL, screen, &position); /* Blit de Perso : */
	  
	  position.x = (LARGEUR_FENETRE / 2) - ((mario->w+luigi->w) / 2) + (personnage->w/2) + 10;
	  position.y = (HAUTEUR_FENETRE / 2) - 2*mario->h;
	  SDL_BlitSurface(mario, NULL, screen, &position); /* Blit de Mario */
	  
	  position.x = (LARGEUR_FENETRE / 2) - (luigi->w / 2) + ((personnage->w + mario->w)/2) + 20;
	  position.y = (HAUTEUR_FENETRE / 2) - 2*luigi->h;
	  SDL_BlitSurface(luigi, NULL, screen, &position); /* Blit de Luigi */
	  
	  position.x = (LARGEUR_FENETRE / 2) - (ok->w / 2);
	  position.y = HAUTEUR_FENETRE - 150;
	  SDL_BlitSurface(ok, NULL, screen, &position); /* Blit du ok */
	  
	  SDL_Flip(screen);
    }
			event.button.x = 0;
			event.button.y = 0;
    TTF_CloseFont(policeTitre);
    TTF_CloseFont(police);

    SDL_FreeSurface(titre);
    SDL_FreeSurface(personnage);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(luigi);

    return;
}