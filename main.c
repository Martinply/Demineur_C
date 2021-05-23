#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entete.h"

int main()
{

    printf("*===================================*\n");
    printf("|                                   |\n");
    printf("|   Bienvenue dans un demineur !!!  |\n");
    printf("|                                   |\n");
    printf("*===================================*\n\n");


    clock_t begin=clock();
    int time_played=1;
    int game_over=0;
    int size = 5;
    float prc = 20;
    int x, y;
    int bomb_number;
    char flag;

    //choose_size(&size);
    //choose_bomb(&prc);

    char **grid_bomb=create_grid(size);
    char **grid_player=create_grid(size);

    put_bomb(grid_bomb, size, &bomb_number, prc);
    put_number(grid_bomb, size);
    //Aff_Grille(grid_bomb, size);


    while(game_over==0){
        if(time_played%2==0)
            print_encouragement();

        Aff_Grille(grid_player, size);
        x=verify_input(size);
        y=verify_input(size);
        flag="";
        flag=put_flag();
        Demasque_case(grid_player, grid_bomb, x, y, flag, size);
        game_over=verification_case(grid_bomb, grid_player, x, y, size, bomb_number);

        time_played++;
        system("cls");
    }


    switch(game_over){
        case 1:
            printf(" ! Felicitation ! Vous avez decouvert toutes les bombes !!!");
            break;
        case 2:
            printf("Felicitation ! Vous avez revele toutes les cases !!!");
            break;
        case 3:
            printf(" !! BOOM !! Vous avez fait exploser une bombe\n");
            break;
    }
    printf("\n");

    Aff_Grille(grid_bomb, size);
    Aff_Grille(grid_player, size);
    clock_t end= clock()-begin;
    long sec= end * 1000 / CLOCKS_PER_SEC;

    printf(" %d seconds %d milliseconds\n", sec/1000, sec%1000);

    free_grid(grid_bomb, size);
    free_grid(grid_player, size);
    return 0;
}
