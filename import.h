#include <string.h>
#include <SDL/SDL.h>
#include <SDL2/SDL_image.h>

#define CACHE_SIZE 5000
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define GROUND_Y 768
#define VELOCITY 2
#define VELOCITY_JUMP 3
#define MARIO_HEIGHT 30
#define MARIO_WIDTH 19
#define MARIO_WALK_R_X 383
#define MARIO_WALK_L_X 446
#define MARIO_WALK_Y 77
#define MARIO_JUMP_R_X 476
#define MARIO_JUMP_L_X 497
#define MARIO_JUMP_Y 35
#define JUMP_HEIGHT 120

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

/*************Variables globales*************/
int LARGEUR_TILE,HAUTEUR_TILE, gameover, saveY;
/*Variables dédiées au défilement de sprites*/
int fly, jump, right, left, step, reset, move;
/**************Rectangles SDL****************/
SDL_Rect perso, posblit;
/***************Surfaces SDL*****************/
SDL_Surface *screen, *mario;