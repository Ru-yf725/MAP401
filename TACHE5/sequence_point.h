#include "types.h"
/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
  Point data;    /* donnée de l'élément de liste */
  struct Cellule_Liste_Point_* suiv; /* pointeur sur l'élément suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
  unsigned int taille;        /* nombre d'éléments dans la liste */
  Cellule_Liste_Point *first; /* pointeur sur le premier élément de la liste */
  Cellule_Liste_Point *last;  /* pointeur sur le dernier élément de la liste */
                         /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
  unsigned int taille; /* nombre d'éléments dans le tableau */
  Point *tab;          /* (pointeur vers) le tableau des éléments */
} Tableau_Point; 

Cellule_Liste_Point *creer_element_liste_Point(Point v);
/* créer une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'élément e en fin de la liste L, renvoie la liste L modifiée */
Liste_Point ajouter_element_liste_Point(Liste_Point* L, Point e);

/* suppression de tous les éléments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concatène L2 à la suite de L1, renvoie la liste L1 modifiée */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* créer une séquence de points sous forme d'un tableau de points 
   à partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* écrire le contour L à l'écran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite accéder aux éléments d'une
   séquence de points par indice */
void ecrire_contour(Liste_Point L);