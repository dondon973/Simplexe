#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 10

struct variables_s{
	int nbr_var;
	char **tab_var;
};
typedef struct variable_s variable_t;

struct contrainte_s{
	int nbr_var;
	char **tab_contrt;
	double *contrt;
};
typedef struct contrainte_s contraint_t;

void model_prob_var(int *nbr_var, char **tab_var){
    int i;
 
    for (i = 0; i < *nbr_var; i++){
       tab_var[i]= (char*)malloc(TAILLE_MAX*sizeof(char));
       printf("Entrer le nom (max 8 caractere) de la variable numero %d : \n",i);
       scanf("%s",tab_var[i]);
    }

}
void model_prob_contr(int *nbr_contrt,char **tab_contrt, double *contrt,int nbr_var,char **tab_var,double **matrice,double *obj){
     int j,k;
    //Donner les contraintes sous forme d'inéquation
	
    for (j = 0; j < *nbr_contrt; j++){
     //  tab_contrt[j]= (char*)malloc(TAILLE_MAX*sizeof(char));
       //matrice[j] = (double*)calloc((nbr_var+(*nbr_contrt)),sizeof(double)); //tableau de dimenstion (n*(m+n)) une matrice
       printf("Entrer le nom (max 8 caractere) de la contrainte numero %d : \n",j);
       scanf("%s",tab_contrt[j]);
       for( k = 0 ; k < nbr_var ; k++){
         printf("entrer le coefficent de %s  dans l'inéquation de la contrainte n:%d (%s) <-",tab_var[k],j+1,tab_contrt[j]);
         scanf("%lf",&matrice[j][k]);
       }
       matrice[j][nbr_var+j]=1;
       printf("Entrer la valeur de la contrainte\n");
       scanf("%lf",&contrt[j]);
	printf("Entrer son coefficent dans la fonction objectif <-:");
       scanf("%lf",&obj[j]);
    }
}

void affichagematrice(int nbr_contrt, char **tab_contrt,double *contrt, int nbr_var, char **tab_var, double **matrice, double *obj){
   int i,j;
   printf("(n-m)=(%d - %d) = %d variables affecté a zéro \n", nbr_contrt,nbr_var,nbr_contrt - nbr_var);
    printf("Voici la matrice PL avec lequel le programme linéaire va travailler\n");
    printf("PL\t");
    for(i = 0; i<nbr_var ; i++){
      printf("%s\t|",tab_var[i]);
    }
    for(i = 0; i<nbr_contrt ; i++){
      printf("%s\t|",tab_contrt[i]);
    }
    printf("\n");
    for (i = 0 ; i<nbr_contrt ; i++){
      printf("%s:\t",tab_contrt[i]);
      for (j=0 ; j < nbr_var+nbr_contrt; j++){
      /*  if(j==nbr_var+i){
          matrice[i][j]==1.0;
        }else if(j >= nbr_var){
          matrice[i][j]=0.0;
        }*/
        printf("%0.2lf\t|",matrice[i][j]);
      }
      printf("%0.2lf",contrt[i]);
      printf("\n");
    }
    printf("obj:\t|");
    for(i = 0; i<nbr_contrt +nbr_var ; i++){
      printf("%0.2lf\t|",obj[i]);
      
    }
    printf("\n");
}

void free_all(int nbr_var,char **tab_var, double *var, int nbr_contrt, char **tab_contrt, double *contrt, double **matrice, double *obj){

    int i;
    for (i = 0 ;i< nbr_var;i++){
      free(tab_var[i]);
    }
    for (i = 0 ;i< nbr_contrt;i++){
      free(tab_contrt[i]);
      free(matrice[i]);
    }
    free(matrice);
    free(tab_contrt);
    free(contrt);
    free(tab_var);
    free(obj);
}

void choix_var_entrante(double *obj, int *indice, int taille){
	double max=0.0;
	int i;
	
	for (i=0; i <taille; i++){
		if(max<obj[i]){
			max=obj[i];
			*indice=i;
		}
	}
	printf("la valeur obj[%d] = %lf est la plus grand \n",*indice, max);
}
void choix_var_sortante(int indice, int nbr_contrt,double **matrice, double *contrainte, int *pivot){
	int i;
	double max;
	double min=999.99;
	double test;	
	
	/*for (i=0; i <(sizeof(*obj)/sizeof(double)); i++){
		if(max<obj[i]){
			max=obj[i];
			*indice=i;
		}
	}*/
	for (i=0 ; i <nbr_contrt ; i++)
	{
		if (matrice[i][indice] != 0){
			test = contrainte[i]/matrice[i][indice];
		}
		if (test < min){
			min= test;
			*pivot = i;
			
		}
	}
	printf("le pivot choisit est a(%d,%d) = %lf \n",*pivot,indice, matrice[*pivot][indice]);
}

void multipleLigne( double **matrice, int n_ligne, double coeff, int taille_ligne, double *cont){
	int i;
	
	for (i=0 ; i< taille_ligne ; i++){
		matrice[n_ligne][i] = matrice[n_ligne][i]*coeff;
	}
	cont[n_ligne] = coeff*cont[n_ligne];
} 

void additionLigne( double **matrice, int n1, int n2 ,double coeff, int taille, double *cont){
	int i;
	for (i=0 ; i< taille ; i++){
		matrice[n1][i] = matrice[n1][i] + matrice[n2][i]*coeff;
	}
	cont[n1]=cont[n1] + cont[n2]*coeff;
}
void pivotage(int indice ,int pivot, double **matrice ,int taille_ligne,int taille_colonne, double *cont, double *obj){
	double facteur;
	int k ;
	
	facteur =1/matrice[pivot][indice];
	multipleLigne(matrice,pivot,facteur, taille_ligne, cont); 
	for ( k = 0 ; k<taille_colonne; k++){
		if (k != pivot){
			additionLigne(matrice, k,pivot, (-matrice[k][indice]),taille_ligne,cont);
		}
		
	}
	int i;
	for (i=0 ; i< taille_colonne ; i++){
		obj[i] = obj[i] - matrice[pivot][i]*obj[i];
	}
}


int verification(double *obj, int taille){
	for (int i= 0 ; i<taille ; i++){
		if(obj[i] >0){
			return 1;
		}
	}
	return 0;
}
int main(int arc, char *arg[]){
    int nbr_var, nbr_contrt,i,j,k;
    char **tab_var;			//tableau des noms des variables
    char **tab_contrt;			//tableau des noms des contraintes
     double *var;			//tableau des valeurs des variables
     double *contrt;			// tableau des valeurs des contraintes
     double *tab_ecart;			//
     double *var_base;			//
     double *var_hbase;			//
    int dim_PL;				// dimension de la matrice PL
     double *obj;			// tableau des coefficents de la fonction objecif
     double **matrice;			//Contstruction de la matrice PL
    char **nom;	
    int indice,pivot;	
	int verif = 1;		
 //   double *obj;

    printf("\n ***************************************************** \n");
    printf("* \t  Bienvenu dans le programme linéaire \t  * \n");
    printf("**************************************************\n");
    printf("Pour résoudre le problème veuiller nous donner les informatiions suivante \n");

    //Entrer les variables du problémes et ceux utilisz dans les equation
 	
    printf("Entrer le nombre de variables du problème :\n");
    scanf("%d",&nbr_var);
    tab_var = (char**)malloc((nbr_var)*sizeof(char*));
    model_prob_var(&nbr_var, tab_var);

    printf("Entrer le nombre de contraintes (d'inéquation) du problème \n");
    scanf("%d",&nbr_contrt);
    tab_contrt = (char**)malloc((nbr_contrt)*sizeof(char*));    //tableau des noms des contraintes
    contrt = (double*)malloc((nbr_contrt)*sizeof(double));      //tableau des valeurs des contraintes
    matrice = (double**)malloc((nbr_contrt)*sizeof(double*));  //Contstruction de la matrice PL
    //tab_var = (char**)calloc((nbr_var+(*nbr_contrt)),sizeof(char*));
     obj = (double*)calloc((nbr_var+(nbr_contrt)),sizeof(double));
	for (j = 0; j < nbr_contrt; j++){
       tab_contrt[j]= (char*)malloc(TAILLE_MAX*sizeof(char));
       matrice[j] = (double*)calloc((nbr_var+(nbr_contrt)),sizeof(double)); //tableau de dimenstion (n*(m+n)) une matri
}

    model_prob_contr(&nbr_contrt,tab_contrt,contrt ,nbr_var,tab_var,matrice,obj);

    affichagematrice(nbr_contrt, tab_contrt, contrt, nbr_var, tab_var, matrice, obj);

	do{

    choix_var_entrante(obj, &indice,nbr_var+(nbr_contrt));

    choix_var_sortante(indice, nbr_contrt,matrice, contrt, &pivot);

	pivotage(indice ,pivot, matrice ,nbr_var+nbr_contrt,nbr_contrt,contrt,obj);

    affichagematrice(nbr_contrt, tab_contrt, contrt, nbr_var, tab_var, matrice, obj);

	verif = verification(obj, nbr_var + nbr_contrt);
	}while(verif != 0);
    free_all(nbr_var,tab_var, var, nbr_contrt, tab_contrt,contrt, matrice, obj);



//Free les matrice et tableau

    
    return 0;
}
