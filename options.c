#include "import.h"

void Options(int *me){
    SDL_Surface *titre, *personnage, *mario, *luigi, *fond;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police, *policeTitre;
    SDL_Color couleurNoire = {0, 0, 0}, couleurRouge = {255, 0, 0};
    int continuer = 1;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Oiram Sorb Beta", NULL);

    fond = IMG_Load("./img/menu/fond.png");
    
    /* Chargement des polices */
    policeTitre = TTF_OpenFont("./fonts/smbfont.ttf", 100);
    police = TTF_OpenFont("./fonts/emulogic.ttf",20);
    
    /* Écriture du texte en mode Blended*/
    titre = TTF_RenderText_Blended(policeTitre, "New Super Oiram Sorb", couleurNoire);
    personnage = TTF_RenderText_Blended(police, "Perso : ", couleurNoire);
    mario = TTF_RenderText_Blended(police, "Mario ", couleurNoire);
    luigi = TTF_RenderText_Blended(police, "Luigi ", couleurNoire);

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
//             case SDL_MOUSEBUTTONDOWN:
// 		  if(event.button.x >= 252  && event.button.x <= (252+new->w) && event.button.y >= 204 && event.button.y <= (204+new->h)){
// 			*me = 1;
// 		  } 
// 		  else if(event.button.x >= 262  && event.button.x <= (262+load->w) && event.button.y >= 253 && event.button.y <= (253+load->h)){
// 			*me = 2;
// 		  } 
//             case SDL_MOUSEMOTION:
//                 if(event.motion.x >= 252  && event.motion.x <= (252+new->w) && event.motion.y >= 204 && event.motion.y <= (204+new->h))
//                     {
//                         texteMenu = TTF_RenderText_Blended(policeMenu,"Nouvelle Partie",couleurRouge);
// 			position.x = (LARGEUR_FENETRE / 2) - (new->w / 2);
// 			position.y = (HAUTEUR_FENETRE / 2) - 2*new->h - 50;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour lancer une nouvelle partie", couleurNoire);
//                         position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
//                         position.y = HAUTEUR_FENETRE - 200;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         SDL_Flip(screen);
//                     }
//                 else if(event.motion.x >= 330  && event.motion.x <= (330+options->w) && event.motion.y >= 298 && event.motion.y <= (298+options->h))
//                     {
//                         texteMenu = TTF_RenderText_Blended(policeMenu,"Options",couleurRouge);
//                         position.x = 330;
//                         position.y = 298;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour modifier vos options", couleurNoire);
//                         position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
//                         position.y = HAUTEUR_FENETRE - 200;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         SDL_Flip(screen);
//                     }
//                 else if(event.motion.x >= 330  && event.motion.x <= (330+credits->w) && event.motion.y >= 348 && event.motion.y <= (348+credits->h))
//                     {
//                         texteMenu = TTF_RenderText_Blended(policeMenu,"Credits",couleurRouge);
//                         position.x = 330;
//                         position.y = 348;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */
//                         texteMenu = TTF_RenderText_Blended(policeInfo,"2018 - DUFOUR 'Zolkovic' Christophe - BEN SAID 'Thundder' Walid", couleurNoire);
//                         position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
//                         position.y = HAUTEUR_FENETRE - 200;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         SDL_Flip(screen);
//                     }
//                 else if(event.motion.x >= 262  && event.motion.x <= (262+load->w) && event.motion.y >= 253 && event.motion.y <= (253+load->h))
//                     {
//                         texteMenu = TTF_RenderText_Blended(policeMenu,"Charger Partie",couleurRouge);
//                         position.x = (LARGEUR_FENETRE / 2) - (load->w / 2);
//                         position.y = (HAUTEUR_FENETRE / 2) - 2*load->h;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
// 			if (compteur != 0){
// 				texteMenu = TTF_RenderText_Blended(policeInfo,"Cliquez pour reprendre l'ancienne partie", couleurNoire);
// 			}else{
// 				texteMenu = TTF_RenderText_Blended(policeInfo,"Aucune sauvegarde existante !", couleurNoire);
// 			}
//                         position.x = (LARGEUR_FENETRE / 2) - (texteMenu->w / 2);
//                         position.y = HAUTEUR_FENETRE - 200;
//                         SDL_BlitSurface(texteMenu, NULL, screen, &position); /* Blit du texte */ 
//                         SDL_Flip(screen);
//                     }
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
        
        position.x = (LARGEUR_FENETRE / 2) - ((mario->w+luigi->w) / 2) + (personnage->w/2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*mario->h;
        SDL_BlitSurface(mario, NULL, screen, &position); /* Blit de Mario */
	
        position.x = (LARGEUR_FENETRE / 2) - (luigi->w / 2) + ((personnage->w + mario->w)/2);
        position.y = (HAUTEUR_FENETRE / 2) - 2*luigi->h;
        SDL_BlitSurface(luigi, NULL, screen, &position); /* Blit de Luigi */
        
        SDL_Flip(screen);
    }

    TTF_CloseFont(policeTitre);
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(titre);
    SDL_FreeSurface(personnage);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(luigi);
    SDL_Quit();

    return;
}