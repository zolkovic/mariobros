typedef struct
{
	char key[SDLK_LAST];
	int spritex;
	int spritey;
	int quit;
} Input;

void UpdateEvents(Input*);
void InitEvents(Input*);
