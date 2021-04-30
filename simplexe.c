#include "simplexe.h"
#include <stdio.h>
#include <stdlib.h>



/* model_prob_v
*/
void model_prob_var(var_t *vars){
    int i;

		printf("Entrer le nombre de variables du problème :\n");
		scanf("%d",&vars->nbr_var);
		vars->tab_var = (char**)malloc((vars->nbr_var)*sizeof(char*));
    for (i = 0; i < vars->nbr_var ; i++){
       vars->tab_var[i]= (char*)malloc(TAILLE_MAX*sizeof(char));
       printf("Entrer le nom (max 8 caractere) de la variable numero %d : \n",i);
       scanf("%s",vars->tab_var[i]);
    }

}

void init_probleme(ProgLin_t *ProgL, contrainte_t *cont, obj_t *objectif){
	int j;
	cont->tab_contrt = (char**)malloc((cont->nbr_contrt)*sizeof(char*));    // Construction du tableau des noms des contraintes
	cont->contrt = (double*)malloc((cont->nbr_contrt)*sizeof(double));      //construction du tableau des valeurs des contraintes
	ProgL->matrice = (double**)malloc((cont->nbr_contrt)*sizeof(double*));  //Contstruction de la matrice PL
	ProgL->nbr_ligne = cont->nbr_contrt;
	//tab_var = (char**)calloc((nbr_var+(*nbr_contrt)),sizeof(char*));
	objectif->obj = (double*)calloc((vars->nbr_var+(cont->nbr_contrt)),sizeof(double)); //Construction du tableau des coeffictents de la fonction objectif
	objectif->taille = vars->nbr_var+(cont->nbr_contrt);			//Affectation de la taille
	for (j = 0; j < cont->nbr_contrt; j++){
		 	cont->tab_contrt[j]= (char*)malloc(TAILLE_MAX*sizeof(char)); 					//Construction de la matrice de contraintes
		 	ProgL->matrice[j] = (double*)calloc((vars->nbr_var+(cont->nbr_contrt)),sizeof(double)); //tableau de dimenstion (n*(m+n)) une matri
		 	ProgL->nbr_colonne = vars->nbr_var+(cont->nbr_contrt);
	 }
}

void model_prob_contr(contrainte_t *cont,var_t *vars,ProgLin_t *ProgL, obj_t *objectif){
     int j,k;
    //Donner les contraintes sous forme d'inéquation
		printf("Entrer le nombre de contraintes (d'inéquation) du problème \n");
	     scanf("%d",&cont->nbr_contrt);

			 	init_probleme(&ProgL, &cont, &objectif)
    for (j = 0; j < cont->nbr_contrt; j++){
     //  tab_contrt[j]= (char*)malloc(TAILLE_MAX*sizeof(char));
       //matrice[j] = (double*)calloc((nbr_var+(*nbr_contrt)),sizeof(double)); //tableau de dimenstion (n*(m+n)) une matrice
       printf("Entrer le nom (max 8 caractere) de la contrainte numero %d : \n",j);
       scanf("%s",cont->tab_contrt[j]);
       for( k = 0 ; k < vars->nbr_var ; k++){
         	printf("entrer le coefficent de %s  dans l'inéquation de la contrainte n:%d (%s) <-",vars->tab_var[k],j+1,cont->tab_contrt[j]);
         	scanf("%lf",&ProgL->matrice[j][k]);
       }
       ProgL->matrice[j][vars->nbr_var+j]=1;
       printf("Entrer la valeur de la contrainte\n");
       scanf("%lf",&cont->contrt[j]);
			 printf("Entrer son coefficent dans la fonction objectif <-:");
       scanf("%lf",&objectif->obj[j]);
    }
}

void affichagematrice(contrainte_t *cont, var_t *vars, ProgLin_t *ProgL, obj_t *objectif){
   int i,j;
   //printf("(n-m)=(%d - %d) = %d variables affecté a zéro \n", nbr_contrt,nbr_var,nbr_contrt - nbr_var);
    printf("Voici la matrice PL avec lequel le programme linéaire va travailler\n");
    printf("PL\t");
    for(i = 0; i<vars->nbr_var ; i++){
      printf("%s\t|",vars->tab_var[i]);
    }
    for(i = 0; i<cont->nbr_contrt ; i++){
      printf("%s\t|",cont->tab_contrt[i]);
    }
    printf("\n");
    for (i = 0 ; i<cont->nbr_contrt ; i++){
      printf("%s:\t",cont->tab_contrt[i]);
      for (j=0 ; j < vars->nbr_var+cont->nbr_contrt; j++){
        printf("%0.2lf\t|",ProgL->matrice[i][j]);
      }
      printf("%0.2lf",cont->contrt[i]);
      printf("\n");
    }
    printf("obj:\t|");
    for(i = 0; i<cont->nbr_contrt +vars->nbr_var ; i++){
      printf("%0.2lf\t|",objectif->obj[i]);

    }
    printf("\n");
}

void free_all(var_t *vars, contrainte_t *cont, ProgLin_t *ProgL, obj_t *objectif){

    int i;
    for (i = 0 ;i< vars->nbr_var;i++){
      free(vars->tab_var[i]);
    }
    for (i = 0 ;i< cont->nbr_contrt;i++){
      free(cont->tab_contrt[i]);
      free(ProgL->matrice[i]);
    }
    free(ProgL->matrice);
    free(cont->tab_contrt);
    free(cont->contrt);
    free(vars->tab_var);
    free(objectif->obj);
}

void choix_var_entrante(obj_t *objectif, int *indice){
	double max=0.0;
	int i;

	for (i=0; i <objectif->taille; i++){
		if(max < objectif->obj[i]){
			max = objectif->obj[i];
			*indice = i;

		}
	}
	printf("la valeur obj[%d] = %lf est la plus grand \n",*indice, max);

}
void choix_var_sortante(int indice, ProgLin_t *ProgL, contrainte_t *cont, int *pivot){
	int i;
	double max;
	double min=999.99;
	double test;

	for (i=0 ; i <ProgL->nbr_ligne ; i++)
	{
		if (ProgL->matrice[i][indice] != 0){
			test = cont->contrt[i]/(ProgL->matrice[i][indice]);
		}
		if (test < min){
			min= test;
			*pivot = i;
			ProgL->pivot = i;
			ProgL->indice=i;

		}
	}
	printf("le pivot choisit est a(%d,%d) = %lf \n",*pivot,indice, ProgL->matrice[*pivot][indice]);
}

void multipleLigne( ProgLin_t *ProgL, int n_ligne, double coeff,  contrainte_t *cont){
	int i;

	for (i=0 ; i< ProgL->nbr_colonne ; i++){
		ProgL->matrice[n_ligne][i] = ProgL->matrice[n_ligne][i]*coeff;
	}
	cont->contrt[n_ligne] = coeff*cont->contrt[n_ligne];
}

void additionLigne( ProgLin_t *ProgL, int n1, int n2 ,double coeff, contrainte_t *cont){
	int i;
	for (i=0 ; i< ProgL->nbr_colonne ; i++){
		ProgL->matrice[n1][i] = ProgL->matrice[n1][i] + ProgL->matrice[n2][i]*coeff;
	}
	cont->contrt[n1]=cont->contrt[n1] + cont->contrt[n2]*coeff;
}

void pivotage(ProgLin_t *ProgL,contrainte_t *cont, obj_t *objectif){
	double facteur, coeff;
	int k ;
	int pivot = ProgL->pivot;
	int indice = ProgL->indice;


	facteur =1/ProgL->matrice[pivot][indice];
	multipleLigne(ProgL,pivot,facteur,  cont);
	for ( k = 0 ; k<ProgL->nbr_ligne; k++){
		if (k != pivot){
			coeff = (-ProgL->matrice[k][indice]);
			additionLigne(ProgL, k,pivot, coeff,cont);
		}

	}
	int i;
	for (i=0 ; i< ProgL->nbr_ligne ; i++){
		objectif->obj[i] = objectif->obj[i] - ProgL->matrice[i][indice]*objectif->obj[i];
	}
}


int verification(obj_t *objectif){
	for (int i= 0 ; i< objectif->taille ; i++){
		if(objectif->obj[i] >0){
			return 1;
		}
	}
	return 0;
}
