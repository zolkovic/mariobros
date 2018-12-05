#include "import.h"
#include "map.c"
#include "events.c"
#include "perso.c"

int main(int argc,char** argv){
	Map* carte;
	Input in;
	gameover = jump = left = right = move = landing = 0;
	step = 1;
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
	while(!gameover)
	{
		printf("%u",landing);
		UpdateEvents(&in);
		Evolue(&in,carte,&perso);
		FocusScrollCenter(carte,&perso);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,screen,mario,carte->xscroll,carte->yscroll);
		SDL_Flip(screen);
		SDL_Delay(10);
	}
	LibererMap(carte);
	SDL_Quit();
	return 0;
}
