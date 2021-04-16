#include "geom2d.h"
#include "contour.h"

#ifndef SIMPLIFICATION
#define SIMPLIFICATION

// Fonction qui s'occupe de la simplification
// par l'algorithme de Douglas Peucker [version segments]
Liste_Point simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d);

// Approximation Bezier 2 d'un contour entre deux indices j1 et j2
Bezier2 approx_bezier2(Contour C, int j1, int j2);

// Fonction qui s'occupe de la simplification
// par l'algorithme de Douglas Peucker [version bezier]
Liste_Point simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d);


#endif