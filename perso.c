#include "import.h"

void RecupererVecteur(Input* in,int* vx,int* vy){
	*vx = *vy = 0;
	/*if (in->key[SDLK_UP])
		*vy = -VELOCITY;
	if (in->key[SDLK_DOWN])
		*vy = VELOCITY;*/
	*vy = VELOCITY;
	if (in->key[SDLK_LEFT])
		*vx = -VELOCITY;
	if (in->key[SDLK_RIGHT])
		*vx = VELOCITY;
	if (in->key[SDLK_SPACE])
		*vy = -VELOCITY;
}

int EssaiDeplacement(Map* carte,SDL_Rect* perso,int vx,int vy){
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

void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy,int LARGEUR_TILE,int HAUTEUR_TILE){
	int i;
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		Deplace(carte,perso,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		Deplace(carte,perso,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		return;
	}
	if (EssaiDeplacement(carte,perso,vx,vy)==1)
		return;
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

void Evolue(Input* in,Map* carte,SDL_Rect* perso,int LARGEUR_TILE,int HAUTEUR_TILE){
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy,LARGEUR_TILE,HAUTEUR_TILE);
}

void AfficherPerso(SDL_Rect *perso,SDL_Rect *posblit,SDL_Surface *screen,SDL_Surface *mario,int xscroll,int yscroll){
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_Rect positionsurimage = *posblit;
	SDL_BlitSurface(mario,&positionsurimage,screen,&positionsurecran);
}