#include "import.h"
#include "map.c"
#include "events.c"
#include "perso.c"

int main(int argc,char** argv){
	SDL_Rect perso, posblit, limit;
	SDL_Surface *screen, *mario;
	Map* carte;
	Input in;
	int LARGEUR_TILE,HAUTEUR_TILE;
	LARGEUR_TILE = 24;
	HAUTEUR_TILE = 16;
	memset(&in,0,sizeof(in));
	SDL_Init(SDL_INIT_VIDEO);		// preapare SDL
	screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	carte = ChargerMap("level2.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	mario = IMG_Load("./img/mario-3.png");
	perso.x = 150;
	perso.y = 150;
	perso.w = 24;
	perso.h = 32;
	posblit.x = MARIO_WALK_R_X;
	posblit.y = MARIO_WALK_Y;
	posblit.w = MARIO_WIDTH;
	posblit.h = MARIO_HEIGHT;
	limit.x = 200;
	limit.y = 150;
	limit.w = 400;
	limit.h = 300;
	while(!in.key[SDLK_ESCAPE])
	{
		UpdateEvents(&in);
		Evolue(&in,carte,&perso,LARGEUR_TILE,HAUTEUR_TILE);
		FocusScrollCenter(carte,&perso);
		FocusScrollBox(carte,&perso,&limit);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,&posblit,screen,mario,carte->xscroll,carte->yscroll);
		SDL_Flip(screen);
		SDL_Delay(5);
	}
	LibererMap(carte);
	SDL_Quit();
	return 0;
}
