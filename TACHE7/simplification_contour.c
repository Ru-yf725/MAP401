#include "simplification_contour.h"
#include <math.h>

Liste_Point simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d)
{
  double dmax = 0;
  int k = j1;
  double dj;
  Liste_Point L, L1, L2;
  L = creer_liste_Point_vide();
  L1 = creer_liste_Point_vide();
  L2 = creer_liste_Point_vide();

  for (int j = j1 + 1 ; j <= j2 ; j++)
  {
    dj = distance_point_segment(C.tab[j], C.tab[j1], C.tab[j2]);
    if (dmax < dj)
    {
      dmax = dj;
      k = j;
    }
  }
  if (dmax <= d)
  {
    ajouter_element_liste_Point(&L, C.tab[j1]);
  }
  else
  {

    L1 = simplification_douglas_peucker(C,j1,k,d);
    L2 = simplification_douglas_peucker(C,k,j2,d);
    L = concatener_liste_Point(L1,L2);
  }
  return L;
}

Bezier2 approx_bezier2(Contour C, int j1, int j2)
{
  double n = j2 - j1;

  Tableau_Point T = sequence_points_liste_vers_tableau(C);

  Bezier2 B2;

  B2.C0 = T.tab[j1];
  B2.C2 = T.tab[j2];

  if (n == 1)
  {
    B2.C1 = add_point(T.tab[j1],T.tab[j2]);
    B2.C1 = mult_Point(0.5,B2.C1);
  }

  else if (n >= 2)
  {

    double alpha = 3*n/(n*n-1);

    double beta = (1-2*n)/(2*(n+1));
    
    // Aux : Auxilary Point
    Point Aux = add_point(T.tab[j1],T.tab[j2]); 

    Aux = mult_Point(beta, Aux);

    B2.C1 = set_point(0,0);

    for (int i = 1 ; i <= (int)n-1 ; i++)
    {
        B2.C1 = add_point(B2.C1,T.tab[j1+i]);
    }

    B2.C1 = mult_Point(alpha, B2.C1);

    B2.C1 = add_point(B2.C1, Aux);

    /*for (int i = 1 ; i < n ; i++)
    {
      printf("dist = %lf\n", distance_point_bezier2(T.tab[i], B2, (double)i/n));
    }*/
  }

  return B2;
}

Liste_Point simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d)
{

  Tableau_Point T = sequence_points_liste_vers_tableau(C);

  Liste_Point L, L1, L2;
  L = creer_liste_Point_vide();
  L1 = creer_liste_Point_vide();
  L2 = creer_liste_Point_vide();
  Bezier3 B3;

  int n = j2-j1;

  Bezier2 B = approx_bezier2(C, j1, j2);

  double dmax = 0;
  int k = j1;

  for (int j = j1 + 1 ; j < j2 ; j++)
  {
    int i = j - j1;

    double ti = (double)i / (double)n;

    double dj = distance_point_bezier2(T.tab[j], B, ti);

    if (dmax < dj)
    {
      dmax = dj;
      k = j;
    }
  }

  if (dmax <= d)
  { 
    L.n = 1;

    /*for (int i = 0 ; i <= n ; i++)
    {
      Point P = BEZIER_2(B, i/(double)n);
      ajouter_element_liste_Point(&L, P);
    }*/
    B3 = Bezier2_to_Bezier3(B);

    ajouter_element_liste_Point(&L, B3.C0);
    ajouter_element_liste_Point(&L, B3.C1);
    ajouter_element_liste_Point(&L, B3.C2);
    ajouter_element_liste_Point(&L, B3.C3);

  }

  else
  {

    L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
    L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);

    L = concatener_liste_Point(L1, L2);
    L.n = L1.n + L2.n;
  }

  return L;
}

