#ifndef GEOM2D_
#define GEOM2D_

#include "types.h"

void afficher_tableau(Tableau_Point T);

void vider_tableau(Tableau_Point* T);

void convert_to_EPS_(Contour C, int mode, Image I, FILE* f);

/* Ajoute les 3 points à Bezier */
Bezier2 add_bezier_2(Point Q0, Point Q1, Point Q2);

#endif