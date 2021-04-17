#include "geom2d.h"
#include <stdio.h>
#include <math.h>

Point set_point(double x, double y)
{
  Point P = {x,y};
  return P;
}

Vecteur set_vecteur(double x, double y)
{
  Vecteur V;

  V.x = x;
  V.y = y;

  return V;
}

// P1 + P2
Point add_point(Point P1, Point P2)
{
  return set_point(P1.x+P2.x, P1.y+P2.y);
}

// P1 - P2
Point soustraction_point(Point P1, Point P2)
{
  return set_point(P1.x-P2.x, P1.y-P2.y);
}

Vecteur vect_bipoint(Point A, Point B)
{
  Vecteur V = {B.x-A.x, B.y-A.y};
  return V;
}

double distance(Point A, Point B)
{
  return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

Vecteur soustraction(Vecteur U, Vecteur V)
{
  Vecteur R = {U.x-V.x, U.y-V.y};
  return R;
}

// Multiplier le vecteur par un scalaire r
// et retourne le vecteur résultant

Vecteur mult_scalaire(double r, Vecteur V)
{
  Vecteur R = {r*V.x,r*V.y};
  return R;
}

Point mult_Point(double k, Point P)
{
  Point p = {k * P.x, k * P.y};
  return p;
}

// Retourne la norme du vecteur V donné en paramètre
double norme_vecteur(Vecteur V)
{
  return sqrtf(pow(V.x,2)+pow(V.y,2));
}

double produit_scalaire(Vecteur V1, Vecteur V2)
{
  return V1.x*V2.x+V1.y*V2.y;
}

// Affiche le point P
void afficher_point(Point P)
{
  printf("(%f,%f)\n", P.x,P.y);
}

// Affiche le vecteur V
void afficher_vecteur(Vecteur V)
{
    printf("(%f,%f)\n", V.x,V.y);
}

double distance_point_segment(Point P, Point A, Point B)
{
    double lambda;
    Point Q;

    if (A.x == B.x && A.y == B.y)
    {
      return distance(A,P);
    }
    else
    {
        lambda = produit_scalaire(vect_bipoint(A,P),vect_bipoint(A,B))/(produit_scalaire(vect_bipoint(A,B), vect_bipoint(A,B)));
        
        if (lambda < 0)
        {
          //printf("lambda < 0\n");

          return distance(A,P);
        }

        else if (lambda >= 0 && lambda <= 1)
        {
          //printf("0 <= lambda <= 1 \n");
          
          Point TMP = soustraction_point(B,A);

          TMP.x = TMP.x * lambda;
          TMP.y = TMP.y * lambda;

          Q = add_point(A,TMP);
          
          return distance(Q,P);
        }
        else
        {
          //printf("lambda > 1\n");
          return distance(B,P);
        }
    }
}

Point BEZIER_2(Bezier2 B, double t)
{
    return (add_point(add_point(
            mult_Point(pow(1-t,2),B.C0),
            mult_Point(2*t*(1-t),B.C1)),
            mult_Point(pow(t,2), B.C2))); 
}

Point BEZIER_3(Bezier3 B, double t)
{
    // Point Auxiliaire
    Point Aux = add_point(mult_Point(
                3*t*pow(1-t,2),B.C1),
                mult_Point(3*pow(t,2)*(1-t),B.C2));
    Aux = add_point(Aux, mult_Point(pow(t,3), B.C3));
    return (add_point(mult_Point(pow((1-t),3),B.C0), Aux));
}

double distance_point_bezier2(Point P, Bezier2 B, double ti)
{
  Point C_ti = BEZIER_2(B, ti);
  return distance(P, C_ti);
}

Bezier3 Bezier2_to_Bezier3(Bezier2 B2)
{
  Bezier3 B3;

  B3.C0 = B2.C0;
  B3.C1 = mult_Point(1.0/3,add_point(B2.C0,mult_Point(2.0, B2.C1)));
  B3.C2 = mult_Point(1.0/3,add_point(B2.C2,mult_Point(2.0, B2.C1)));
  B3.C3 = B2.C2;

  return B3;
}


double distance_point_bezier3(Point P, Bezier3 B, double ti)
{
  Point C_ti = BEZIER_3(B, ti);
  return distance(P, C_ti);
}

