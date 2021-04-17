#include "sequence_point.h"
#include <stdio.h>  /* utilisation des entrées-sorties standard de C */
#include <stdlib.h> /* utilisation des fonctions malloc et free */


Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;

	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	
	el->data = v;
	el->suiv = NULL;

	return el;
}


Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}


Liste_Point ajouter_element_liste_Point(Liste_Point* L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L->taille == 0)
	{
		/* premier élément de la liste */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
	return *L;
}


Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas où l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier élément de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}



Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'élément dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'élément dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrémenter k */
		el = el->suiv; /* passer à l'élement suivant dans la liste chainee */
	}
	
	return T;
}


void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("%d points : [", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* récupérer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}

Bezier2 add_bezier_2(Point Q0, Point Q1, Point Q2)
{
	Bezier2 B2;

	B2.C0 = Q0;
	B2.C1 = Q1;
	B2.C2 = Q2;

	return B2;
}





