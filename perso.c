#include "import.h"

void RecupererVecteur(Input* in,int* vx,int* vy){
	*vx = 0;
	//gravité qui permet à Mario de tomber s'il doit tomber
	*vy = VELOCITY;
	if (fin==0){
		if (move != 0){
            if (pouvoir==1){
                if (move>0)
                    *vx = move+3;
                else
                    *vx = move-3;
            }else{
                *vx = move;
            }
		}
		if (jump && perso.y > saveY-JUMP_HEIGHT)
			*vy = -VELOCITY_JUMP;
		else
			jump = 0;
		if (perso.y >= GROUND){
			vie -= 1;
			if (vie != 0){
				perso.x = respawnX;
				perso.y = respawnY;
			}
			SDL_Delay(100);
		}
	}
}

void ViePerso(){
	if (vie==3){
		vies = IMG_Load("./img/3_lives.png");
	} else if (vie==2){
		vies = IMG_Load("./img/2_lives.png");
	} else if (vie==1){
		vies = IMG_Load("./img/1_life.png");
	} else {
		vies = IMG_Load("./img/0_life.png");
	}
	SDL_Rect positionsurecran;
	positionsurecran.x = 10;
	positionsurecran.y = 50;
	SDL_BlitSurface(vies,NULL,screen,&positionsurecran);
	if (vie == 0){
		gameover = 1;
		Mix_Chunk* end;
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
		end = Mix_LoadWAV("./sons/game-over.wav");
		Mix_PlayChannel(6, end, 0);
	}
}

int EssaiDeplacement(Map* carte,SDL_Rect* perso,int vx,int vy,int compteur,int *pieces){
	SDL_Rect test;
	test = *perso;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(carte,&test,compteur,pieces)==0){
		*perso = test;
		return 1;
	}
	return 0;
}

void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy, int compteur,int *pieces){
	int i;
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		Deplace(carte,perso,vx/2,vy/2,compteur,pieces);
		Deplace(carte,perso,vx-vx/2,vy-vy/2,compteur,pieces);
		return;
	}
	if (EssaiDeplacement(carte,perso,vx,vy,compteur,pieces)==1)
		return;
	for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(carte,perso,SGN(vx),0,compteur,pieces)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(carte,perso,0,SGN(vy),compteur,pieces)==0)
			break;			
	}
}

void Evolue(Input* in,Map* carte,SDL_Rect* perso,int compteur,int *pieces){
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy, compteur,pieces);
	SDL_Delay(30);
	/*Sauvegarde de la position Y au cas où Mario veuille sauter*/
	if (fin==0){
		if (!jump && !fly){
			saveY=perso->y;
			respawnY=perso->y;
			respawnX=perso->x;
		}
		/*Si Mario est en chute on met un save hors de map pour éviter les sauts dans le vide*/
		else if(!jump && fly)
			saveY = 9999;
		/*Quand Mario saute vers la DROITE*/
		if (fly && right){
			step = 1;
            if (pouvoir==0){
                posblit.x = MARIO_JUMP_R_X;
            }else if(pouvoir==1){
                if(posblit.x == MARIO_JUMP_POWER_DEBUT_R_X
                    || posblit.x == MARIO_JUMP_POWER_DEBUT_R_X + (MARIO_WIDTH + 2)
                    || posblit.x == MARIO_JUMP_POWER_DEBUT_R_X + 2*(MARIO_WIDTH + 2)){
                        posblit.x += MARIO_WIDTH + 2;
                }else{
                    posblit.x = MARIO_JUMP_POWER_DEBUT_R_X;
                }
            }
			posblit.y = MARIO_JUMP_Y;
		}
		/*Quand Mario saute vers la GAUCHE*/
		if (fly && left){
			step = 4;
            if (pouvoir==0){
                posblit.x = MARIO_JUMP_L_X;
            }else if(pouvoir==1){
                if(posblit.x == MARIO_JUMP_POWER_DEBUT_L_X
                    || posblit.x == MARIO_JUMP_POWER_DEBUT_L_X + (MARIO_WIDTH + 2)
                    || posblit.x == MARIO_JUMP_POWER_DEBUT_L_X + 2*(MARIO_WIDTH + 2)){
                        posblit.x += MARIO_WIDTH + 2;
                }else{
                    posblit.x = MARIO_JUMP_POWER_DEBUT_L_X;
                }
            }
			posblit.y = MARIO_JUMP_Y;
		}
		/*Si Mario n'est pas en l'air*/
		if (!fly)
		{
		  /*Quand Mario marche vers la DROITE*/
		  if (move==VELOCITY){
			if (step < 1 || step > 3){
				step = 1;
			}
			if (step == 3){
				reset = 1;
			}
			if (step == 1){
                if(pouvoir==0){
                    posblit.x = MARIO_WALK_R_X;
                }else if(pouvoir==1){
                    posblit.x = MARIO_POWER_R_X;
                }
				posblit.y = MARIO_WALK_Y;
				reset = 0;
			}
			if (reset == 0){
				posblit.x += MARIO_WIDTH + 2;
				step++;
			}
			if (reset == 1){
				posblit.x -= MARIO_WIDTH + 2;
				step--;
			}
		  }
		  /*Quand Mario marche vers la GAUCHE*/
		  else if (move==-VELOCITY){
			posblit.y = MARIO_WALK_Y;
			if (step < 4 || step > 6){
				step = 4;
			}
			if (step == 6){
				reset = 1;
			}
			if (step == 4){
                if (pouvoir==0){
                    posblit.x = MARIO_WALK_L_X;
                }else if(pouvoir==1){
                    posblit.x = MARIO_POWER_L_X;
                }
				posblit.y = MARIO_WALK_Y;
				reset = 0;
			}
			if (reset == 0){
				posblit.x += MARIO_WIDTH + 2;
				step+=1;
			}
			if (reset == 1){
				posblit.x -= MARIO_WIDTH + 2;
				step--;
			}
		  }
		  /*Quand Mario s'arrête*/
		  else if (move==0){
			if (step>=4 && step<=6){
                if (pouvoir==0){
                    posblit.x = MARIO_WALK_L_X;
                }else if(pouvoir==1){
                    posblit.x = MARIO_POWER_L_X;
                }
				posblit.y = MARIO_WALK_Y;
				step = 4;
			}
			else if (step>=1 && step<=3){
                if (pouvoir==0){
                    posblit.x = MARIO_WALK_R_X;
                }else if(pouvoir==1){
                    posblit.x = MARIO_POWER_R_X;
                }
                posblit.y = MARIO_WALK_Y;
				step = 1;
			}
		  }
		}
	}else if (fin!=0){
		/*Ici on ne contrôle plus Mario puisque c'est la fin, donc on l'anime*/
		if (posblit.x != 761){
			posblit.x += MARIO_WIDTH + 2;
		}
		if (perso->x < (fin)*32-10){
			perso->x += 1;
		}else{
            gameover = 1;
            SDL_Delay(2000);
        }
	}
}

void AfficherPerso(SDL_Rect *perso,SDL_Surface *screen,SDL_Surface *mario,int xscroll,int yscroll){
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_BlitSurface(mario,&posblit,screen,&positionsurecran);
	ViePerso();
}
