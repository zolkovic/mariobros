#include "import.h"
#include "map.c"
#include "events.c"
#include "perso.c"

int main(int argc,char** argv){
	Map* carte;
// 	Mix_Music* musique;
	Input in;
	gameover = jump = left = right = move = fly = 0;
	step = 1;
	LARGEUR_TILE = 24;
	HAUTEUR_TILE = 16;
	memset(&in,0,sizeof(in));
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // preapare SDL video ET audio
	TTF_Init(); //prepare SDL fonts 
	
	TTF_Font *police = NULL;
	SDL_Color couleurBlanche = {255, 255, 255};
	screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	carte = ChargerMap("level2.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	mario = IMG_Load("./img/mario-3.png");
	police = TTF_OpenFont("./fonts/emulogic.ttf", 65);
	texte = TTF_RenderText_Blended(police, "Test Mario Bros !", couleurBlanche);
// 	musique = Mix_LoadMUS("./sons/mario-bros-song.mp3");
	perso.x = 30;
	perso.y = saveY = 600;
	perso.w = 24;
	perso.h = 32;
	posblit.x = MARIO_WALK_R_X;
	posblit.y = MARIO_WALK_Y;
	posblit.w = MARIO_WIDTH;
	posblit.h = MARIO_HEIGHT;
	postexte.x = 100;
	postexte.y = 150;
	
// 	Mix_PlayMusic(musique, -1);
	while(!gameover)
	{
		UpdateEvents(&in);
		Evolue(&in,carte,&perso);
		FocusScrollCenter(carte,&perso);
		AfficherMap(carte,screen);
		AfficherPerso(&perso,screen,mario,carte->xscroll,carte->yscroll);
		SDL_BlitSurface(texte, NULL, screen, &postexte);
		SDL_Flip(screen);
		SDL_Delay(10);
	}
// 	Mix_FreeMusic(musique);
	TTF_CloseFont(police); 
	LibererMap(carte);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
