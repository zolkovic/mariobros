#include "import.h"

void RecupererVecteur(Input* in,int* vx,int* vy){
	*vx = 0;
	*vy = VELOCITY;
	if (move == -1){
		*vx = -VELOCITY;
	}
	if (move == 1){
		*vx = VELOCITY;
	}
	if (jump){
		*vy = -VELOCITY;
	}
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

void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy){
	int i;
	if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		Deplace(carte,perso,vx/2,vy/2);
		Deplace(carte,perso,vx-vx/2,vy-vy/2);
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

void Evolue(Input* in,Map* carte,SDL_Rect* perso){
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy);
	/*Quand Mario saute vers la DROITE*/
	if (landing && right){
	  step = 1;
	  posblit.x = MARIO_JUMP_R_X;
	  posblit.y = MARIO_JUMP_Y;
	}
	/*Quand Mario saute vers la GAUCHE*/
	if (landing && left){
	  step = 4;
	  posblit.x = MARIO_JUMP_L_X;
	  posblit.y = MARIO_JUMP_Y;
	}
	/*Si Mario n'est pas en l'air*/
	if (!landing)
	{
	  /*Quand Mario marche vers la DROITE*/
	  if (move==1){
	    if (step != 1 && step != 2 && step != 3){
	      posblit.x = MARIO_WALK_R_X;
	      posblit.y = MARIO_WALK_Y;
	      step = 1;
	    }
	    if (step == 3){
	      reset = 1;
	    }
	    if (step == 1){
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
	  else if (move==-1){
	    posblit.y = MARIO_WALK_Y;
	    if (step != 4 && step != 5 && step != 6){
	      posblit.x = MARIO_WALK_L_X;
	      posblit.y = MARIO_WALK_Y;
	      step = 4;
	    }
	    if (step == 6){
	      reset = 1;
	    }
	    if (step == 4){
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
	      if (step==4 || step==5 || step==6){
		posblit.x = MARIO_WALK_L_X;
		posblit.y = MARIO_WALK_Y;
		step = 4;
	      }
	      else if (step==1 || step==2 || step==3){
		posblit.x = MARIO_WALK_R_X;
		posblit.y = MARIO_WALK_Y;
		step = 1;
	      }
	  }
	}
	/*Quand Mario ratterit*/
// 	if (landing==1){
// 	  landing = 0;
// 	  posblit.y = MARIO_WALK_Y;
// 	  if (left){
// 	    posblit.x = MARIO_WALK_L_X;
// 	  }else if (right){
// 	    posblit.x = MARIO_WALK_R_X;
// 	  }
// 	}

}

void AfficherPerso(SDL_Rect *perso,SDL_Surface *screen,SDL_Surface *mario,int xscroll,int yscroll){
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_BlitSurface(mario,&posblit,screen,&positionsurecran);
}