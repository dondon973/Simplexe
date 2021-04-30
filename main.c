#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simplexe.h"

int main(int arc, char *arg[]){

	int verif = 1;
var_t var_bases;
contrainte_t cont;
ProgLin_t PL_mat;
 obj_t objectif;
   int indice,pivot;
    printf("\n ***************************************************** \n");
    printf("* \t  Bienvenu dans le programme linéaire \t  * \n");
    printf("**************************************************\n");
    printf("Pour résoudre le problème veuiller nous donner les informatiions suivante \n");

    model_prob_var(&var_bases);



    model_prob_contr(&cont, &var_bases, &PL_mat,&objectif);

    affichagematrice(&cont, &var_bases, &PL_mat, &objectif);

	do{

    choix_var_entrante(&objectif,&indice);

    choix_var_sortante(indice,&PL_mat, &cont, &pivot);

	pivotage(&PL_mat, &cont, &objectif);

    affichagematrice(&cont, &var_bases, &PL_mat, &objectif);

	verif = verification(&objectif);
}while(verif != 0);
    free_all(&var_bases, &cont, &PL_mat, &objectif);


//Free les matrice et tableau


    return 0;
}
