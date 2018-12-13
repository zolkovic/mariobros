#include "editeur_map.c"
#include "editeur_events.c"
#include <unistd.h>

#define MAX_LARGEUR_FENETRE 800
#define MAX_HAUTEUR_FENETRE 600 

typedef struct
{
	char levelfic[500];
	Input I;
	int toggletileset;
	int toggleHV;
	int reaffiche;
	int selectedtile;
	Map* m;
} Context;

void MoveMap(Map* m,Input* in,int movespeed)
{
	if (in->key[SDLK_LEFT])
		m->xscroll-=movespeed;
	if (in->key[SDLK_RIGHT])
		m->xscroll+=movespeed;
	if (in->key[SDLK_UP])
		m->yscroll-=movespeed;
	if (in->key[SDLK_DOWN])
		m->yscroll+=movespeed;
// limitation
	if (m->xscroll<0)
		m->xscroll=0;
	if (m->yscroll<0)
		m->yscroll=0;
	if (m->xscroll>m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1)
		m->xscroll=m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1;
	if (m->yscroll>m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1)
		m->yscroll=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1;
}

void VideoResizeForLevel(Map* m)
{
	char buf[50];
	int xtaillereelle,ytaillereelle;
	xtaillereelle = m->LARGEUR_TILE*m->nbtiles_largeur_monde-1;
	ytaillereelle = m->HAUTEUR_TILE*m->nbtiles_hauteur_monde-1;
	if (xtaillereelle>MAX_LARGEUR_FENETRE)
		xtaillereelle = MAX_LARGEUR_FENETRE;
	if (ytaillereelle>MAX_HAUTEUR_FENETRE)
		ytaillereelle = MAX_HAUTEUR_FENETRE;
	SDL_SetVideoMode(xtaillereelle, ytaillereelle, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	m->largeur_fenetre = xtaillereelle;
	m->hauteur_fenetre = ytaillereelle;
	sprintf(buf,"Taille : %d x %d",m->nbtiles_largeur_monde,m->nbtiles_hauteur_monde);
	SDL_WM_SetCaption(buf,NULL);
}

void Affmurs(Map* m)
{
	int i,j,numtile;
	for(i=0,numtile=0;i<m->nbtilesX;i++)
	{
		for(j=0;j<m->nbtilesY;j++,numtile++)
		{
			if (m->props[numtile].mur)
				SDL_FillRect(SDL_GetVideoSurface(),&m->props[numtile].R,SDL_MapRGBA(SDL_GetVideoSurface()->format,255,0,255,0));
		}
	}
}

void SizeChangeCheck(Context* C)
{
	int nsize[2];
	nsize[0] = C->m->nbtiles_largeur_monde;
	nsize[1] = C->m->nbtiles_hauteur_monde;
	if (C->I.key[SDLK_h])
		C->toggleHV = 0;
	if (C->I.key[SDLK_v])
		C->toggleHV = 1;
	if (C->I.mousebuttons[SDL_BUTTON_WHEELDOWN])
		nsize[C->toggleHV]++;
	if (C->I.mousebuttons[SDL_BUTTON_WHEELUP])
		nsize[C->toggleHV]--;
	if (nsize[0]<1 || nsize[1]<1)
		return;  // taille invalide : ignore.
	if (nsize[0]==C->m->nbtiles_largeur_monde && nsize[1]==C->m->nbtiles_hauteur_monde)
		return;  // pas de changement
	ResizeMap(C->m,nsize[0],nsize[1]);
 	VideoResizeForLevel(C->m);
	while(0);
}

int EditOnMap(Context* C)
{
	int xpos,ypos;
	SDL_Rect Rdest;
	if (C->reaffiche)
		VideoResizeForLevel(C->m);
	MoveMap(C->m,&C->I,1);
	AfficherMap(C->m,SDL_GetVideoSurface());
	xpos = (C->I.mousex+C->m->xscroll)/C->m->LARGEUR_TILE;
	ypos = (C->I.mousey+C->m->yscroll)/C->m->HAUTEUR_TILE;
	Rdest.x = xpos * C->m->LARGEUR_TILE - C->m->xscroll;
	Rdest.y = ypos * C->m->HAUTEUR_TILE - C->m->yscroll;
	SDL_BlitSurface(C->m->tileset,&C->m->props[C->selectedtile].R,SDL_GetVideoSurface(),&Rdest);
	if (C->I.mousebuttons[SDL_BUTTON_LEFT])
		C->m->schema[xpos][ypos] = C->selectedtile;
	if (C->I.key[SDLK_LCTRL] && C->I.key[SDLK_s])
	{
		SauverMap(C->levelfic,C->m);
		SDL_WM_SetCaption("SAUVEGARDE FAITE",NULL);
	}
	SizeChangeCheck(C);
	return 0;
}

int EditOnTileset(Context* C)
{
	int localselectedtile;
	if (C->reaffiche)
		SDL_SetVideoMode(C->m->tileset->w, C->m->tileset->h, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_BlitSurface(C->m->tileset,NULL,SDL_GetVideoSurface(),NULL);
	localselectedtile = (C->I.mousex/C->m->LARGEUR_TILE) + C->m->nbtilesX*(C->I.mousey/C->m->HAUTEUR_TILE);
	if (C->I.key[SDLK_LCTRL])
	{
		if (C->I.mousebuttons[SDL_BUTTON_LEFT])
		{
			C->I.mousebuttons[SDL_BUTTON_LEFT] = 0;
			C->m->props[localselectedtile].mur = 1 - C->m->props[localselectedtile].mur;
		}
		Affmurs(C->m);
	}
	else
	{
		if (C->I.mousebuttons[SDL_BUTTON_LEFT])
		{
			C->I.mousebuttons[SDL_BUTTON_LEFT] = 0;
			C->selectedtile = localselectedtile;
			return 1;
		}
	}
	return 0;
}

int Editeur(Context* C)
{
	while(!C->I.key[SDLK_ESCAPE] && !C->I.quit)
	{
		UpdateEvents(&C->I);
		if (C->I.mousebuttons[SDL_BUTTON_RIGHT])
		{
			C->I.mousebuttons[SDL_BUTTON_RIGHT] = 0;
			C->toggletileset = 1 - C->toggletileset;
			C->reaffiche = 1;
		}
		if (C->toggletileset==0) // map
			EditOnMap(C);
		else
		{
			if(EditOnTileset(C)==1)
				C->I.mousebuttons[SDL_BUTTON_RIGHT] = 1;
		}
		C->reaffiche = 0;
		SDL_Flip(SDL_GetVideoSurface());
		SDL_Delay(1);
	}
	return 0;
}

int LoadLevel(Context* C,const char* fic)
{
	Map* m;
	SDL_SetVideoMode(MAX_LARGEUR_FENETRE, MAX_HAUTEUR_FENETRE, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	m = ChargerMap(fic,MAX_LARGEUR_FENETRE,MAX_HAUTEUR_FENETRE);
	VideoResizeForLevel(m);
	C->m = m;
	strcpy(C->levelfic,fic);
	Editeur(C);
	LibererMap(m);
	return 0;
}

int NewLevel(Context* C,const char* fic)
{
	int nbxtile,nbytile;
	Map* m;
	strcpy(C->levelfic,fic);
	strcpy(C->levelfic+strlen(C->levelfic)-3,"txt");
	printf("Nombre de tiles horizontalement : ");
	scanf("%d",&nbxtile);
	printf("Nombre de tiles verticalement : ");
	scanf("%d",&nbytile);
	SDL_SetVideoMode(MAX_LARGEUR_FENETRE, MAX_HAUTEUR_FENETRE, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	m = NewMap(fic,nbxtile,nbytile,10,10);
	VideoResizeForLevel(m);
	C->m = m;
	Editeur(C);
	LibererMap(m);
	return 0;
} 

int Lancer(const char* param)
{
	Context C;
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE);		// prepare SDL
	memset(&C,0,sizeof(Context));
	InitEvents(&C.I);
	if (strcmp(param+strlen(param)-3,"txt")==0)
		LoadLevel(&C,param);
	if (strcmp(param+strlen(param)-3,"bmp")==0)
		NewLevel(&C,param);
	SDL_Quit();
	return 0;
}

void getdirfrom(const char* fic)
{
	char buf[500];
	int i,nb = strlen(fic);
	strcpy(buf,fic);
	for(i=nb-1;i>=0;i--)
		if (buf[i]=='\\' || buf[i]=='/')
		{
			buf[i]='\0';
			break;
		}
}

int main(int argc,char** argv)
{
	char buf[500];
	getcwd(buf,500);
	//printf("path = %s\n",buf);
	if (argc!=2)
	{
		char buf[500];
		FILE* F;
		printf("Nom du fichier bmp ou txt\n");
		scanf("%s",buf);
		F = fopen(buf,"r");
		if (F==NULL)
		{
			printf("Fichier introuvable\n");
			system("pause");
			return -1;
		}
		fclose(F);
		return Lancer(buf);
	}
	//printf("argv1 : %s\n",argv[1]);
	getdirfrom(argv[1]);
	chdir(argv[1]);
	return Lancer(argv[1]);
}
