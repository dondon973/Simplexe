#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simplexe.h"

int main(int arc, char *arg[]){

	int verif = 1;  //Verifie le critere d'arret de l'algorithme.
	var_t var_bases;  //structure contenant le nombres de variables ,leur noms.
	contrainte_t cont; // structure contenans le nombre d'inéquations ,les valeurs des contraintes ,et les noms des variables virtuels.
	ProgLin_t PL_mat;  // structure contenat le tableau PL
	 obj_t objectif;  //Structure qui modelise la fonction objectif pour faire les opérations de pivotage et vérifier la condition de la solution optimale 
 
   int indice,pivot;  // indices de la ligne et de la colonne du pivot.
    printf(" ***************************************************** \n");
    printf("* \t  Bienvenu dans le programme linéaire \t  * \n");
    printf("**************************************************\n");
    printf("Pour résoudre le problème veuiller nous donner les informatiions suivante \n");

 //Construction du tableau du programme linéaire 

    model_prob_var(&var_bases);  //Donne le nombre de variables et leurs noms 

    model_prob_contr(&cont, &var_bases, &PL_mat,&objectif); // donne le nombre de contraintes ou d'inéqations ainsique les noms des variables virtuels 

    affichagematrice(&cont, &var_bases, &PL_mat, &objectif); //affichge du tableau 

	do{

    choix_var_entrante(&objectif,&indice);  //Choisis l'indice de la colonne du pivot

    choix_var_sortante(indice,&PL_mat, &cont, &pivot); //choisis l'indice de la ligne du pivot

	pivotage(&PL_mat, &cont, &objectif);  // realise les opérations du pivotage

    affichagematrice(&cont, &var_bases, &PL_mat, &objectif);  ///affiche la matrice obtenue 

	verif = verification(&objectif);  //verifie les conditon pour une solution optimale
}while(verif != 0);
    free_all(&var_bases, &cont, &PL_mat, &objectif); //libere la mémoire allouée par


//Free les matrice et tableau


    return 0;
}
