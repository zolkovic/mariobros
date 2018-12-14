#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
//#include "dll/include/SDL/SDL_mixer.h"
#include <SDL/SDL_ttf.h>

#define CACHE_SIZE 5000
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define GROUND 600
#define VELOCITY 7
#define VELOCITY_JUMP 12
#define MARIO_HEIGHT 30
#define MARIO_WIDTH 19
#define MARIO_WALK_R_X 383
#define MARIO_WALK_L_X 446
#define MARIO_WALK_Y 77
#define MARIO_JUMP_R_X 476
#define MARIO_JUMP_L_X 497
#define MARIO_JUMP_Y 35
#define JUMP_HEIGHT 128 //4 TILES
#define SPAWN_X 30
#define SPAWN_Y 535
#define NB_LEVELS 5
#define NB_MONDES 2

#define COLLISION_GAUCHE 1
#define COLLISION_DROITE 2
#define COLLISION_HAUT 3
#define COLLISION_BAS 4

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))
void AfficherTemps(int*, int*);
/*************Variables globales*************/
int LARGEUR_TILE,HAUTEUR_TILE, gameover, saveY, vie, respawnX, respawnY, score, i, compteur, monde, level, me, highscore_int, score;
/*Variables dédiées au défilement de sprites*/
int fly, jump, right, left, step, reset, move, fin;
/**************Rectangles SDL****************/
SDL_Rect perso, posblit, postexte;
/***************Surfaces SDL*****************/
SDL_Surface *screen, *mario, *texte, *vies;
