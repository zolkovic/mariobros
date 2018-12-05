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
			if (event.key.keysym.sym==SDLK_RIGHT || event.key.keysym.sym==SDLK_LEFT){
			  move = 0;
			}
			if (event.key.keysym.sym==SDLK_SPACE){
			  jump = 0;
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
				jump = 1;
				break;
			case SDLK_LEFT:
				right = 0;
				left = 1;
				move = -1;
				break;
			case SDLK_RIGHT:
				left = 0;
				right = 1;
				move = 1;
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