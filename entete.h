#ifndef ENTETE_H_INCLUDED
#define ENTETE_H_INCLUDED

char ** create_grid(int size);

void init_grid(char **tab, int size);

void Aff_Grille(char **tab, int size);

void put_bomb(char **tab, int size, int *bomb_number, float prc);

void put_number(char **tab, int size);

void choose_size(int *size);

void choose_bomb(float *prc);

int verify_input(int size);

int verification_case(char **tab_bomb, char** tab_play, int x, int y, int size, int nbmax);

void Demasque_case(char **grille_visible, char **grille_cache, int x, int y, char flag, int size);

char put_flag();

void print_encouragement();

int verification_victory(char **tab_bomb, char **tab_play, int size, int nbmax);

void free_grid(char **tab, int size);

#endif // ENTETE_H_INCLUDED

