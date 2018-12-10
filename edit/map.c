#include <string.h>
#include <SDL/SDL.h>
#define FMAP_CACHE_SIZE 500

typedef struct
{
	SDL_Rect R;
	int mur;
} TileProp;

typedef struct
{
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	SDL_Surface* tileset;
	char tilesetname[FMAP_CACHE_SIZE];
	TileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
	int xscroll,yscroll;
	int largeur_fenetre,hauteur_fenetre;
} Map;

SDL_Surface* LoadImage32(const char* fichier_image)
{
	SDL_Surface* image_result;
	SDL_Surface* image_ram = SDL_LoadBMP(fichier_image);	// charge l'image dans image_ram en RAM
	if (image_ram==NULL)
	{
		printf("Image %s introuvable !! \n",fichier_image);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	image_result = SDL_DisplayFormat(image_ram);
	SDL_FreeSurface(image_ram);
	return image_result;
}

void CommonBuild_tileset(FILE* F,Map* m)
{
	int numtile,i,j;
	char buf[FMAP_CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[FMAP_CACHE_SIZE];  // un buffer, petite mémoire cache
	strcpy(buf2,"mur");
	m->LARGEUR_TILE = m->tileset->w/m->nbtilesX;
	m->HAUTEUR_TILE = m->tileset->h/m->nbtilesY;
	m->props = malloc(m->nbtilesX*m->nbtilesY*sizeof(TileProp));
	for(j=0,numtile=0;j<m->nbtilesY;j++)
	{
		for(i=0;i<m->nbtilesX;i++,numtile++)
		{
			m->props[numtile].R.w = m->LARGEUR_TILE;
			m->props[numtile].R.h = m->HAUTEUR_TILE;
			m->props[numtile].R.x = i*m->LARGEUR_TILE;
			m->props[numtile].R.y = j*m->HAUTEUR_TILE;
			if (F)
				fscanf(F,"%s %s",buf,buf2);
			m->props[numtile].mur = 0;
			if (strcmp(buf2,"mur")==0)
				m->props[numtile].mur = 1;
		}
	}
}

void ChargerMap_tileset(FILE* F,Map* m)
{
	char buf[FMAP_CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	fscanf(F,"%s",buf); // nom du fichier
	strcpy(m->tilesetname,buf);
	m->tileset = LoadImage32(buf);
	fscanf(F,"%d %d",&m->nbtilesX,&m->nbtilesY);
	CommonBuild_tileset(F,m);
}

void CommonBuild_level(FILE* F,Map* m)
{
	int i,j;
	m->schema = malloc(m->nbtiles_largeur_monde*sizeof(Uint16*));
	for(i=0;i<m->nbtiles_largeur_monde;i++)
		m->schema[i] = malloc(m->nbtiles_hauteur_monde*sizeof(Uint16));
	for(j=0;j<m->nbtiles_hauteur_monde;j++)
	{
		for(i=0;i<m->nbtiles_largeur_monde;i++)
		{
			int tmp = 0;
			if (F)
				fscanf(F,"%d",&tmp);
			if (tmp>=m->nbtilesX*m->nbtilesY)
			{
				printf("level tile hors limite\n");
				SDL_Quit();
				system("pause");
				exit(-1);
			}
			m->schema[i][j] = tmp;
		}
	}
}

void ChargerMap_level(FILE* F,Map* m)
{
	char buf[FMAP_CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #level
	fscanf(F,"%d %d",&m->nbtiles_largeur_monde,&m->nbtiles_hauteur_monde);
	CommonBuild_level(F,m);
}

Map* ChargerMap(const char* level,int largeur_fenetre,int hauteur_fenetre)
{
	FILE* F;
	Map* m;
	F = fopen(level,"r");
	if (!F)
	{
		printf("fichier %s introuvable !! \n",level);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	m = malloc(sizeof(Map));
	ChargerMap_tileset(F,m);
	ChargerMap_level(F,m);
	m->largeur_fenetre = largeur_fenetre;
	m->hauteur_fenetre = hauteur_fenetre;
	m->xscroll = 0;
	m->yscroll = 0;
	fclose(F);
	return m;
}

int AfficherMap(Map* m,SDL_Surface* screen)
{
	int i,j;
	SDL_Rect Rect_dest;
	int numero_tile;
	int minx,maxx,miny,maxy;
	minx = m->xscroll / m->LARGEUR_TILE;
	miny = m->yscroll / m->HAUTEUR_TILE;
	maxx = (m->xscroll + m->largeur_fenetre)/m->LARGEUR_TILE;
	maxy = (m->yscroll + m->hauteur_fenetre)/m->HAUTEUR_TILE;
	for(i=minx;i<=maxx;i++)
	{
		for(j=miny;j<=maxy;j++)
		{
			Rect_dest.x = i*m->LARGEUR_TILE - m->xscroll;
			Rect_dest.y = j*m->HAUTEUR_TILE - m->yscroll;
			numero_tile = m->schema[i][j];
			SDL_BlitSurface(m->tileset,&(m->props[numero_tile].R),screen,&Rect_dest);
		}
	}
	return 0;
}

int LibererMap(Map* m)
{
	int i;
	SDL_FreeSurface(m->tileset);
	for(i=0;i<m->nbtiles_largeur_monde;i++)
		free(m->schema[i]);
	free(m->schema);
	free(m->props);
	free(m);
	return 0;
}

int SauverMap(const char* fic,Map* m)
{
	int i,j;
	FILE* F = fopen(fic,"w");
	if (!F)
		return -1;
	fprintf(F,"#tileset\n%s\n",m->tilesetname);
	fprintf(F,"%d %d\n",m->nbtilesX,m->nbtilesY);
	for(i=0;i<m->nbtilesX*m->nbtilesY;i++)
		fprintf(F,"tile%d: %s\n",i,(m->props[i].mur)?("mur"):("ciel"));
	fprintf(F,"#level\n%d %d\n",m->nbtiles_largeur_monde,m->nbtiles_hauteur_monde);
	for(j=0;j<m->nbtiles_hauteur_monde;j++)
	{
		for(i=0;i<m->nbtiles_largeur_monde;i++)
		{
			fprintf(F,"%d \t",m->schema[i][j]);
		}
		fprintf(F,"\n");
	}
	fclose(F);
	return 0;
}

int ResizeMap(Map* m,int nouvelletailleX,int nouvelletailleY)
{
	int i,j;
	Uint16** anc = m->schema;	
	m->schema = malloc(nouvelletailleX*sizeof(Uint16*));
// alloc nouveau
	for(i=0;i<nouvelletailleX;i++)
		m->schema[i] = malloc(nouvelletailleY*sizeof(Uint16));
	for(i=0;i<nouvelletailleX;i++)
	{
		for(j=0;j<nouvelletailleY;j++)
		{
			if (i<m->nbtiles_largeur_monde && j<m->nbtiles_hauteur_monde)
				m->schema[i][j] = anc[i][j];
			else
				m->schema[i][j] = 0;
		}
	}
// delete l'ancien.
	for(i=0;i<m->nbtiles_largeur_monde;i++)
		free(anc[i]);
	free(anc);
// assign dims.
	m->nbtiles_largeur_monde = nouvelletailleX;
	m->nbtiles_hauteur_monde = nouvelletailleY;
	return 0;
}

Map* NewMap(const char* tileset,int nbtilesX,int nbtilesY,int nbtiles_largeur_monde,int nbtiles_hauteur_monde)
{
	Map* m = malloc(sizeof(Map));
	strcpy(m->tilesetname,tileset);
	m->tileset = LoadImage32(tileset);
	m->nbtiles_largeur_monde = nbtiles_largeur_monde;
	m->nbtiles_hauteur_monde = nbtiles_hauteur_monde;
	m->nbtilesX = nbtilesX;
	m->nbtilesY = nbtilesY;
	CommonBuild_tileset(NULL,m);
	CommonBuild_level(NULL,m);
	m->xscroll = 0;
	m->yscroll = 0;
	m->hauteur_fenetre = 10;
	m->largeur_fenetre = 10;
	return m;
}
