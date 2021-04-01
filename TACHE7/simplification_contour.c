#include "simplification_contour.h"

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

/*Liste_Point simplification_douglas_peucker_bezier2(Contour C, int j1, int j2, double d)
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
    //ajouter_element_liste_Point(&L, C.tab[j2]);
  }
  else
  {

    L1 = simplification_douglas_peucker(C,j1,k,d);
    L2 = simplification_douglas_peucker(C,k,j2,d);
    L = concatener_liste_Point(L1,L2);
  }
  return L;
}*/