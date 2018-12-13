#include "import.h"
#include "map.c"
#include "events.c"
#include "perso.c"

void playGame(int me, int monde, int level, int *compteur, int vie, int respawnX, int respawnY){
	Map* carte;
	Input in;
	gameover = jump = left = right = move = fly = i = 0;	step = 1;	score = 00000;
	LARGEUR_TILE = 24;
	HAUTEUR_TILE = 16;
	memset(&in,0,sizeof(in));
	if (monde==1){
		if (level==1)
			carte = ChargerMap("level1.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
		//le reste des maps ici...
	}
	switch (me){
		case 1:
			mario = IMG_Load("./img/mario-3.png");
			break;
		case 2:
			mario = IMG_Load("./img/luigi-3.png");
			break;
	}
	perso.x = respawnX;
	perso.y = saveY = respawnY;
	perso.w = 19;
	perso.h = 30;
	posblit.x = MARIO_WALK_R_X;
	posblit.y = MARIO_WALK_Y;
	posblit.w = MARIO_WIDTH;
	posblit.h = MARIO_HEIGHT;
    
	//Affichage du temps
	int tempsActuel = 0, tempsPrecedent = 0;
	SDL_Surface *temps = NULL, *chrono = NULL;
	char time[10] = "";
	/* Initialisation du temps et du texte */
	TTF_Font *policeMenu = NULL;
	policeMenu = TTF_OpenFont("./fonts/emulogic.ttf",20);
	SDL_Color couleurBlanche = {255, 255, 255};
	/* Écriture du texte en mode Solid*/
	temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche);
	while(!gameover)
	{
		UpdateEvents(&in);
		Evolue(&in,carte,&perso);
		FocusScrollCenter(carte,&perso);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,screen,mario,carte->xscroll,carte->yscroll);
		TableauDeBord(screen, me);
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent >= 1000) /* Si 1000 ms au moins se sont écoulées */
		{
		    *compteur -= 1; /* On rajoute 1s au compteur */
		    sprintf(time, "Timer : %d", *compteur); /* On écrit dans la chaîne "temps" le nouveau temps */
		    SDL_FreeSurface(temps); /* On supprime la surface précédente */
		    temps = TTF_RenderText_Solid(policeMenu, time, couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surface */
		    tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
		}
		postexte.x = LARGEUR_FENETRE - temps->w - 5;
		postexte.y = temps->h - 20;
		SDL_BlitSurface(temps, NULL, screen, &postexte); /* Blit du temps*/
		postexte.x -= 20;
		SDL_BlitSurface(chrono, NULL, screen, &postexte); /* Blit du chronomètre */
		SDL_Flip(screen);
	}
	LibererMap(carte);
	return;
}
