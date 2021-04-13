#include "geom2d.h"
#include "contour.h"

#ifndef SIMPLIFICATION
#define SIMPLIFICATION

Liste_Point simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d);

Bezier2 approx_bezier2(Contour C, int j1, int j2);

double gamma_(double k, double n);

Bezier3 approx_bezier3(Contour C, int j1, int j2);

Liste_Point simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d);

Liste_Point simplification_douglas_peucker_bezier3(Contour C, int j1, int j2, double d);

#endif