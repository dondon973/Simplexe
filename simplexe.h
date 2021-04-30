// Auteur : JEAN-FRANOIS Brandon
// Simplexe.h
#define TAILLE_MAX 10

struct variables_s{
	int nbr_var;
	char **tab_var;
};
typedef struct variables_s var_t;

struct contrainte_s{
	int nbr_contrt;
  double *contrt;
	char **tab_contrt;

};
typedef struct contrainte_s contrainte_t;

struct objectif_s{
  int taille;
  double *obj;

};
typedef struct objectif_s obj_t;

struct ProgLin_s{
  int nbr_ligne;
  int nbr_colonne;
  double **matrice;
  obj_t obj;
  int pivot;
  int indice;

};
typedef struct ProgLin_s ProgLin_t;

void model_prob_var(var_t *vars);
void init_probleme(ProgLin_t *ProgL, contrainte_t *cont, obj_t *objectif, var_t *vars);
void model_prob_contr(contrainte_t *cont,var_t *vars,ProgLin_t *ProgL, obj_t *objectif);
void affichagematrice(contrainte_t *cont, var_t *vars, ProgLin_t *ProgL, obj_t *objectif);
void choix_var_entrante(obj_t *objectif, int *indice);
void choix_var_sortante(int indice, ProgLin_t *ProgL, contrainte_t *cont, int *pivot);
void multipleLigne( ProgLin_t *ProgL, int n_ligne, double coeff,  contrainte_t *cont);
void additionLigne( ProgLin_t *ProgL, int n1, int n2 ,double coeff, contrainte_t *cont);
void pivotage(ProgLin_t *ProgL,contrainte_t *cont, obj_t *objectif);
int verification(obj_t *objectif);
void free_all(var_t *vars, contrainte_t *cont, ProgLin_t *ProgL, obj_t *objectif);
