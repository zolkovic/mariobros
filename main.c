#include "map.c"
#include "events.c"

#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define VELOCITY 2
#define MARIO_HEIGHT 30
#define MARIO_WIDTH 19
#define MARIO_WALK_R_X 383
#define MARIO_WALK_L_X 446
#define MARIO_WALK_Y 77

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

void RecupererVecteur(Input* in,int* vx,int* vy)
{
	//int vitesse = 2;
	*vx = *vy = 0;
	if (in->key[SDLK_UP])
		*vy = -VELOCITY;
	if (in->key[SDLK_DOWN])
		*vy = VELOCITY;
	if (in->key[SDLK_LEFT])
		*vx = -VELOCITY;
	if (in->key[SDLK_RIGHT])
		*vx = VELOCITY;
}

int EssaiDeplacement(Map* carte,SDL_Rect* perso,int vx,int vy)
{
	SDL_Rect test;
	test = *perso;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(carte,&test)==0)
	{
		*perso = test;
		return 1;
	}
	return 0;
}

void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	int i;
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		Deplace(carte,perso,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		Deplace(carte,perso,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		return;
	}
	if (EssaiDeplacement(carte,perso,vx,vy)==1)
		return;
// affine
	for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(carte,perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(carte,perso,0,SGN(vy))==0)
			break;			
	}
}

void Evolue(Input* in,Map* carte,SDL_Rect* perso,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy,LARGEUR_TILE,HAUTEUR_TILE);
}

void AfficherPerso(SDL_Rect *perso,SDL_Rect *posblit,SDL_Surface *screen,SDL_Surface *mario,int xscroll,int yscroll)
{
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_Rect positionsurimage = *posblit;
	SDL_BlitSurface(mario,&positionsurimage,screen,&positionsurecran);
	//SDL_FillRect(screen,&positionsurecran,0x00FF00); 
}

int main(int argc,char** argv)
{
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
