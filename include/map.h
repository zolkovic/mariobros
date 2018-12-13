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
	TileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
	int xscroll,yscroll;
	int largeur_fenetre,hauteur_fenetre;
} Map;

SDL_Surface* LoadImage32(const char*);
void ChargerMap_tileset(FILE*,Map*);
void ChargerMap_level(FILE*,Map*);
Map* ChargerMap(const char*,int,int);
int AfficherMap(Map*,SDL_Surface*);
int LibererMap(Map*);
int CollisionDecor(Map*,SDL_Rect*);
void ClampScroll(Map*);
int FocusScrollCenter(Map*,SDL_Rect*);
int FocusScrollBox(Map*,SDL_Rect*,SDL_Rect*);
