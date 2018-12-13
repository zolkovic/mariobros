#include "import.h"

void playGame(){
	Map* carte;
	Input in;
	gameover = jump = left = right = move = fly = i = 0;	step = 1;	vie = 3;	score = 00000;
	LARGEUR_TILE = 24;
	HAUTEUR_TILE = 16;
	memset(&in,0,sizeof(in));
	
	carte = ChargerMap("level1.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	mario = IMG_Load("./img/mario-3.png");
	perso.x = respawnX = 30;
	perso.y = saveY = respawnY = 535;
	perso.w = 24;
	perso.h = 32;
	posblit.x = MARIO_WALK_R_X;
	posblit.y = MARIO_WALK_Y;
	posblit.w = MARIO_WIDTH;
	posblit.h = MARIO_HEIGHT;
    
    //Affichage du temps
    int tempsActuel = 0, tempsPrecedent = 0;
    SDL_Surface *temps = NULL, *chrono = NULL;
    char time[10] = "";
    /* Initialisation du temps et du texte */
    tempsActuel = SDL_GetTicks();
    sprintf(time, "%d", compteur);
    TTF_Font *policeMenu = NULL;
    policeMenu = TTF_OpenFont("./fonts/emulogic.ttf",20);
    SDL_Color couleurBlanche = {255, 255, 255};
    /* Écriture du texte en mode Solid*/
    temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche);
    chrono = IMG_Load("./img/menu/xchrono.png");
	while(!gameover)
	{
		UpdateEvents(&in);
		Evolue(&in,carte,&perso);
		FocusScrollCenter(carte,&perso);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,screen,mario,carte->xscroll,carte->yscroll);
		TableauDeBord(screen);
        ////////////
        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent >= 1000) /* Si 1000 ms au moins se sont écoulées */
        {
            compteur += 1; /* On rajoute 1s au compteur */
            sprintf(time, "%d", compteur); /* On écrit dans la chaîne "temps" le nouveau temps */
            SDL_FreeSurface(temps); /* On supprime la surface précédente */
            temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surface */
            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
        }

        postexte.x = LARGEUR_FENETRE - temps->w - 5;
        postexte.y = temps->h - 20;
        SDL_BlitSurface(temps, NULL, screen, &postexte); /* Blit du temps*/

        postexte.x -= 20;
        SDL_BlitSurface(chrono, NULL, screen, &postexte); /* Blit du chronomètre */
        ////////////
		SDL_Flip(screen);
		SDL_Delay(8);
	}
	LibererMap(carte);
	return;
}
