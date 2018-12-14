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

SDL_Surface* read_highscore(SDL_Surface* highscore, TTF_Font* police,SDL_Color couleur){
    FILE* fichier = NULL;
    char highscore_string[10] ="";
    fichier = fopen("highscore.txt", "r");
    fscanf(fichier, "%d", &highscore_int);
    fclose(fichier);
    sprintf(highscore_string, "Highscore :\n %08u",highscore_int); /* On écrit dans la chaîne "temps" le nouveau temps */
    return TTF_RenderText_Blended(police,highscore_string, couleur);
}

// void write_infos_load_game(){
//     FILE* fichier = NULL;
//     fichier = fopen("charger_partie.txt", "w");
//     // On l'écrit dans le fichier
//     fprintf(fichier, "%d", );
//     fclose(fichier);
// }
