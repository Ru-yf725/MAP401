#include "geom2d.h"
#include <stdio.h>
#include <math.h>

Point set_point(double x, double y)
{
  Point P = {x,y};
  return P;
}

Point add_point(Point P1, Point P2)
{
  return set_point(P1.x+P2.x, P1.y+P2.y);
}

Vecteur vect_bipoint(Point A, Point B)
{
  Vecteur V = {B.x-A.x, B.y-A.y};
  return V;
}

double distance(Point A, Point B)
{
  return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

Vecteur soustraction(Vecteur U, Vecteur V)
{
  Vecteur R = {U.x-V.x, U.y-V.y};
  return R;
}

Vecteur mult_scalaire(double r, Vecteur V)
{
  Vecteur R = {r*V.x,r*V.y};
  return R;
}

double norme_vecteur(Vecteur V)
{
  return sqrt(V.x*V.x+V.y*V.y);
}

void afficher_point(Point P)
{
  printf("(%f,%f)\n", P.x,P.y);
}

void afficher_vecteur(Vecteur V)
{
    printf("(%f,%f)\n", V.x,V.y);
}

