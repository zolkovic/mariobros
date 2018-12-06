#include "import.h"

typedef struct
{
	char key[SDLK_LAST];
	int spritex;
	int spritey;
	int quit;
} Input;

void UpdateEvents(Input* in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameover = 1;
			break;
		case SDL_KEYUP:
		{
			in->key[event.key.keysym.sym]=0;
			switch(event.key.keysym.sym)
			{
			case SDLK_SPACE:
				jump = 0;
				break;
			case SDLK_RIGHT:
				//condition if pour pas que Mario s'arrête si on enchaine des droite/gauche
				if (move == VELOCITY)
					move = 0;
				break;
			case SDLK_LEFT:
				//condition if pour pas que Mario s'arrête si on enchaine des droite/gauche
				if (move == -VELOCITY)
					move = 0;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			in->key[event.key.keysym.sym]=1;
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				gameover = 1;
				break;
			case SDLK_SPACE:
				//condition pour éviter de pouvoir sauter dans les airs
				if (perso.y > saveY-1 && !jump)
					jump = 1;
				break;
			case SDLK_LEFT:
				right = 0;
				left = 1;
				move = -VELOCITY;
				break;
			case SDLK_RIGHT:
				left = 0;
				right = 1;
				move = VELOCITY;
				break;
			}
			break;
		}
		break;
		}
	}
}

void InitEvents(Input* in)
{
	memset(in,0,sizeof(Input));
}