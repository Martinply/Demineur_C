#include "entete.h"
#include <stdio.h>
#include <stdlib.h>

//Fonction qui créé la grille
char ** create_grid(int size){
    int i;
    char **tab=(char**)malloc(sizeof(char*)*size);
    for(i=0; i<size;i++){
        tab[i]=(char*)malloc(sizeof(char)*size);
    }
    init_grid(tab, size);
    return tab;
}

//Fonction qui initialise la grille
void init_grid(char **tab, int size){

    int i, j;
    for(i=0; i<size; i++){
        for(j=0;j<size; j++){
            tab[i][j]=0;
        }
    }
}

//Fonction qui affiche la grille
void Aff_Grille(char ** tab, int size){
    int i, j, k;
    printf("   ");
    for (i = 0; i <  size; i++)
        printf("  %2d ", i);
    printf("\n    ");

    for (k = 0; k <  size; k++)
            printf("  |  ");
    printf("\n    |");

    for (k = 0; k <  size; k++)
            printf("----+");
    printf("\n");

    for (i = 0; i <  size; i++){
        printf(" %2d-|", i);
        for (j = 0; j < size; j++){
            if(tab[i][j]==0){
               printf("  - |");
            }
            else if(tab[i][j]== ' '){
               printf("    |");
            }
            else if(tab[i][j]<71 && tab[i][j]>64){
                printf("  %c |", tab[i][j]);
            }
            else{
                printf(" %2i |", tab[i][j]);
            }

        }
        printf("\n    |");
        for (k = 0; k <  size; k++)
            printf("----+");
        printf("\n");
    }
}

//Fonction qui dispose les mines
void put_bomb(char **tab, int size, int *bomb_number, float prc){
    int x, y;
    int installed=0;
    //int nbmax=size*size*0.2;
    int nbmax=size*size*(prc/100);
    do{
        x=rand()%size;
        y=rand()%size;
        if(tab[x][y]==0){
            tab[x][y]='B';
            installed++;
        }
    }while(installed<nbmax);
    *bomb_number=installed;
}

//Fonction qui ajoute les nombres autour des bombes
void put_number(char **tab, int size){
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(tab[i][j]=='B'){
                if(i-1>=0){
                   if(tab[i-1][j]!='B') tab[i-1][j] += 1;

                    if(j-1>=0){
                        if(tab[i-1][j-1]!='B') tab[i-1][j-1] += 1;
                    }
                    if(j+1<size){
                        if(tab[i-1][j+1]!='B') tab[i-1][j+1] += 1;
                    }
                }

                if(j-1>=0){
                    if(tab[i][j-1]!='B') tab[i][j-1] += 1;
                }

                if(j+1<size){
                    if(tab[i][j+1]!='B') tab[i][j+1] += 1;
                }

                if(i+1<size){
                   if(tab[i+1][j]!='B') tab[i+1][j] += 1;
                    if(j-1>=0){
                        if(tab[i+1][j-1]!='B') tab[i+1][j-1] += 1;
                    }
                    if(j+1<size){
                        if(tab[i+1][j+1]!='B') tab[i+1][j+1] += 1;
                    }
                }
            }

        }

    }
}

//Fonction qui permet d'enregistrer la taille
void choose_size(int *size){
    int tmp=0;
    do{
        printf("Saisir la taille de la grille : ");
        scanf("%i", &tmp);
        printf("\n");
    }while(tmp<=1 || tmp >= 50);
    *size=tmp;
}

//Fonction qui permet d'enregistrer le nombre de bombe
void choose_bomb(float *prc){
    float tmp=0;
    do{
        printf("Saisir le pourcentage de bombes dans la grille : ");
        scanf("%f", &tmp);
        printf("\n");
    }while(tmp<1 || tmp>100);
    *prc=tmp;

}

//Fonction qui vérifie la saisie de l'utilisateur
int verify_input(int size){

	int x;
	do{
	printf("Entrez une coordonees: ");
	scanf("%d", &x);
	}while(x<0 || x>size);
	return x;
}

//Fonction qui vérifie ce que contient la case séléctionnée
int verification_case(char **tab_bomb, char** tab_play, int x, int y, int size, int nbmax){
    if(tab_play[x][y]=='B'){
        return 3;
    }
    return verification_victory(tab_bomb, tab_play, size, nbmax);
}

//Fonction qui révèle la case joué
void Demasque_case(char **grille_visible, char **grille_cache, int x, int y, char flag, int size){
    if(flag=='F')
        grille_visible[x][y]='F';
    else if(grille_cache[x][y] == 0){
        int tab[8] = {0};
        tab[0] = -1;
        //printf("///////%i\n", tab[7]);
        print_recursif(grille_cache, grille_visible, size, x, y, tab);
        grille_visible[x][y]=' ';
    }else
        grille_visible[x][y]=grille_cache[x][y];
}

//Fonction qui pose les drapeaux
char put_flag(){
    char flag= 0;
    do{
        fflush(stdin);
        printf("\nTapez F si vous voulez poser un drapeau et N sinon : ");
        scanf("%c", &flag);
    }while(flag!='F' && flag != 'N');

    return flag;
}

//Fonction qui affiche les encouragement
void print_encouragement(){
    int a=0;
    char tab_encouregement[4][30] = {"Bon courage ! \n",
                                "Tu peux le faire ! \n",
                                "Tu es sur la bonne voie ! \n",
                                "Continue, lache pas ! \n",};
    a=rand()%4;
    printf("%s", tab_encouregement[a]);
    printf("\n");
}

//Fonction qui vérifie la fin du jeu
int verification_victory(char **tab_bomb, char **tab_play, int size, int nbmax){
    int c=0, i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size;j++){
                if(tab_bomb[i][j]=='B' && tab_play[i][j]=='F')
                    c++;
        }
    }

    if(c==nbmax)
        return 1;

    for(i=0; i<size; i++){
        for(j=0; j<size;j++){
                if(tab_play[i][j]==0 && tab_bomb[i][j]!='B')
                    return 0;
        }
    }
    return 2;
}

//Fonction qui libère la grille
void free_grid(char **tab, int size){
    int i;
    for(i=0; i<size; i++){
        free(tab[i]);
    }
    free(tab);
}

void print_recursif(char **tab_bomb, char **tab_play, int size, int i, int j, int *tab){
    int tmp = 0;
    if(tab[0]==-1){
        if(i-1>=0){
           if(tab_bomb[i-1][j]==0){
                tab_play[i-1][j]=' ';
                tab[1] = 1;
                tmp = 1;
                //print_recursif(tab_bomb, tab_play, size, i-1, j);
           }
           if(j-1>=0){
                if(tab_bomb[i-1][j-1]==0){
                    tab_play[i-1][j-1]=' ';
                    tab[0] = 1;
                    tmp = 1;
                    //print_recursif(tab_bomb, tab_play, size, i-1, j-1);
                }
            }

            if(j+1<size){
                if(tab_bomb[i-1][j+1]==0){
                    tab_play[i-1][j+1]=' ';
                    tab[2] = 1;
                    tmp = 1;
                    //print_recursif(tab_bomb, tab_play, size, i-1, j+1);
                }
            }
        }

        if(j-1>=0){
            if(tab_bomb[i][j-1]==0){
                tab_play[i][j-1]=' ';
                tab[3] = 1;
                tmp = 1;
                //print_recursif(tab_bomb, tab_play, size, i, j-1);
            }
        }

        if(j+1<size){
            if(tab_bomb[i][j+1]==0){
                tab_play[i][j+1]=' ';
                tab[4] = 1;
                tmp = 1;
                //print_recursif(tab_bomb, tab_play, size, i, j+1);
            }
        }

        if(i+1<size){
           if(tab_bomb[i+1][j]==0){
                tab_play[i+1][j]=' ';
                tab[6] = 1;
                tmp = 1;
                //print_recursif(tab_bomb, tab_play, size, i+1, j);
           }
            if(j-1>=0){
                if(tab_bomb[i+1][j-1]==0)
                    tab_play[i+1][j-1]=' ';
                    tab[5] = 1;
                    tmp = 1;
                    //print_recursif(tab_bomb, tab_play, size, i+1, j-1);
            }
            if(j+1<size){
                if(tab_bomb[i+1][j+1]==0){
                    tab_play[i+1][j+1]=' ';
                    tab[7] = 1;
                    tmp = 1;
                   //print_recursif(tab_bomb, tab_play, size, i+1, j+1);
                }
            }
        }

    }else{
        if(tab[0] == 1)
            print_recursif(tab_bomb, tab_play, size, i-1, j-1, NULL);
        if(tab[1] == 1)
            print_recursif(tab_bomb, tab_play, size, i-1, j, NULL);
        if(tab[2] == 1)
            print_recursif(tab_bomb, tab_play, size, i, j-1, NULL);
        if(tab[3] == 1)
            print_recursif(tab_bomb, tab_play, size, i, j+1, NULL);
        if(tab[4] == 1)
            print_recursif(tab_bomb, tab_play, size, i+1, j-1, NULL);
        if(tab[5] == 1)
            print_recursif(tab_bomb, tab_play, size, i+1, j, NULL);
        if(tab[6] == 1)
            print_recursif(tab_bomb, tab_play, size, i+1, j-1, NULL);
    }
    if(tmp != 0)
        print_recursif(tab_bomb, tab_play, size, i+1, j-1, tab);

}

