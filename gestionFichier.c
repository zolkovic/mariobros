#include "import.h"
void write_highscore(int score){
    int last_highscore;
    FILE* fichier = NULL;
    fichier = fopen("highscore.txt", "w");
    // On l'écrit dans le fichier
    fscanf(fichier, "%d", &last_highscore);
    if(score > last_highscore)
      fprintf(fichier, "%d", score);
    fclose(fichier);
}

void creer_sauvegarde(int score, int x, int y, int vies, int monde, int level, int compteur, int me){
	FILE* fichier;
	fichier = fopen("sauvegarde.txt", "w+");
	fprintf(fichier,"%u %u %u %u %u %u %u %u",score,x,y,vies,monde,level,compteur, me);
	fclose(fichier);
}

void charger_sauvegarde(int *score, int *x, int *y, int *vies, int *monde, int *level, int *compteur, int *me){
	FILE* fichier;
	fichier = fopen("sauvegarde.txt", "r");
	int donnes[10] = {0};
	fscanf(fichier,"%u %u %u %u %u %u %u %u",&donnes[0],&donnes[1],&donnes[2],&donnes[3],&donnes[4],&donnes[5],&donnes[6], &donnes[7]);
	*score = donnes[0];
	*x = donnes[1];
	*y = donnes[2];
	*vies = donnes[3];
	*monde = donnes[4];
	*level = donnes[5];
	*compteur = donnes[6];
	*me = donnes[7];
	fclose(fichier);
}

SDL_Surface* read_highscore(SDL_Surface* highscore, TTF_Font* police,SDL_Color couleur){
    FILE* fichier = NULL;
    char highscore_string[10] ="";
    fichier = fopen("highscore.txt", "r");
    fscanf(fichier, "%d", &highscore_int);
    fclose(fichier);
    sprintf(highscore_string, "%08u",highscore_int); /* On écrit dans la chaîne "temps" le nouveau temps */
    return TTF_RenderText_Blended(police,highscore_string, couleur);
}
