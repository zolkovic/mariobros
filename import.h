#include <string.h>
#include <SDL/SDL.h>
#include <SDL2/SDL_image.h>

#define CACHE_SIZE 5000
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
