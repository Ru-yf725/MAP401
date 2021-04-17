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

  int n = j2-j1;

  Bezier2 B2 = approx_bezier2(C, j1, j2);

  Bezier3 B = Bezier2_to_Bezier3(B2);

  double dmax = 0;
  int k = j1;

  for (int j = j1 + 1 ; j < j2 ; j++)
  {
    int i = j - j1;

    double ti = (double)i / (double)n;

    double dj = distance_point_bezier3(T.tab[j], B, ti);

    if (dmax < dj)
    {
      dmax = dj;
      k = j;
    }
  }

  if (dmax <= d)
  { 

    L.n = 1;

  	ajouter_element_liste_Point(&L, B.C0);
  	ajouter_element_liste_Point(&L, B.C1);
  	ajouter_element_liste_Point(&L, B.C2);
    ajouter_element_liste_Point(&L, B.C3);
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

Liste_Point simplification_douglas_peucker_bezier3(Contour C, int j1, int j2, double d)
{

  Tableau_Point T = sequence_points_liste_vers_tableau(C);

  Liste_Point L, L1, L2;
  L = creer_liste_Point_vide();
  L1 = creer_liste_Point_vide();
  L2 = creer_liste_Point_vide();

  int n = j2-j1;

  Bezier3 B = approx_bezier3(C, j1, j2);

  double dmax = 0;
  int k = j1;

  for (int j = j1 + 1 ; j < j2 ; j++)
  {
    int i = j - j1;

    double ti = (double)i / (double)n;

    double dj = distance_point_bezier3(T.tab[j], B, ti);

    if (dmax < dj)
    {
      dmax = dj;
      k = j;
    }
  }

  if (dmax <= d)
  { 

  	L.n = 1;

    ajouter_element_liste_Point(&L, B.C0);
    ajouter_element_liste_Point(&L, B.C1);
    ajouter_element_liste_Point(&L, B.C2);
    ajouter_element_liste_Point(&L, B.C3);

  }

  else
  {
    
    L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
    L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);

    L = concatener_liste_Point(L1, L2);
    L.n = L1.n + L2.n - 2;
  }
  return L;
}

double gamma_(double k, double n)
{
  return 6*pow(k,4)-8*n*pow(k,3)+6*k*k-4*n*k+pow(n,4)-n*n;
}

Bezier3 approx_bezier3(Contour C, int j1, int j2)
{
  
  double n = j2 - j1;

  Tableau_Point T = sequence_points_liste_vers_tableau(C);

  Bezier3 B3;

  B3.C0 = T.tab[j1];
  B3.C3 = T.tab[j2];

  if (n < 3)
  {
   // B3.C1 = mult_Point(1.0/3, add_point(T.tab[1],mult_Point(2, T.tab[0])));
   // B3.C2 = mult_Point(1.0/3, add_point(T.tab[1],mult_Point(2, T.tab[0])));
  	Bezier2 B2 = approx_bezier2(C,j1,j2);
  	B3 = Bezier2_to_Bezier3(B2);
  }

  else
  {
    double alpha = ((-15)*pow(n,3)+5*n*n+2*n+4)/(3*(n+2)*(3*n*n+1));

    double beta = (10*pow(n,3)-15*n*n+n+2)/(3*(n+2)*(3*n*n+1));

    double lambda = (70*n)/(3*(n*n-1)*(n*n-4)*(3*n*n+1));
    
    // Aux : Auxilary Point
    Point C1 = mult_Point(alpha, T.tab[j1]);
    C1 = add_point(C1, mult_Point(beta, T.tab[j2]));

    Point C2 = mult_Point(beta, T.tab[j1]);
    C2 = add_point(C2 , mult_Point(alpha, T.tab[j2]));

    Point Cumul_C1 = set_point(0,0);
    Point Cumul_C2 = set_point(0,0);

    for (int i = 1 ; i <= (int)n-1 ; i++)
    {
      Cumul_C1 = add_point(Cumul_C1, mult_Point(gamma_(i,n),T.tab[j1+i]));
      Cumul_C2 = add_point(Cumul_C2 ,mult_Point(gamma_(n-i,n),T.tab[j1+i]));
    }

    Cumul_C1 = mult_Point(lambda, Cumul_C1);
    Cumul_C2 = mult_Point(lambda, Cumul_C2);

    B3.C1 = add_point(C1, Cumul_C1);
    B3.C2 = add_point(C2, Cumul_C2);
  }

  /*for (int i = 1 ; i < n ; i++)
    {
      printf("dist = %lf\n", distance_point_bezier3(T.tab[i], B3, (double) i/n));
    }*/

  return B3;
}

void convert_to_EPS_(Contour C, int mode, Image I, FILE* f)
{
    if (C.taille == 0)
    {
        fprintf(stderr, "Le Contour est vide !\n");
        return;
    }

    /* Headers du fichier EPS */
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n");

    // Cellule d'itération
    Cellule_Liste_Point* current = C.first->suiv->suiv->suiv->suiv; 

    if (mode == 1) // Mode contour avec segments
    {
        fprintf(f,"newpath\n");

        fprintf(f, "%.1f %.1f m %.1f %.1f l\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y);

        Point previous_point;

        while (current != NULL)
        {
            previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f l\n", previous_point.x, I.H-previous_point.y, current->suiv->data.x, I.H-current->suiv->data.y);
            current = current->suiv->suiv->suiv->suiv;
        }


        fprintf(f, "\n0 setlinewidth\ns\n");

        fprintf(f,"closepath\n");

    }

    else if (mode == 2) // Mode segments + points
    {   

        // Ci-dessous, l'affichage se fait en 2 étapes :
        // 1ère étape : on affiche les segments
        // 2ème étape en affiche les points
        // Compléxité : O(n+n) = O(2n) = O(n)

        // On commence d'abord par les points

        fprintf(f,"newpath\n");

        while (current->suiv != NULL)
        {
            fprintf(f, "\nnewpath\n%.1f %.1f 0.3 0 360 arc\nfill\nclosepath\n", current->data.x, I.H-current->data.y);
            current = current->suiv;
        }


        // Après on remet l'itérateur current à la position initiale
        // et on parcours encore une fois la liste pour afficher les segments

        fprintf(f, "%.1f %.1f m %.1f %.1f l\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y);

        current = C.first;

        Point previous_point;

        while (current->suiv != NULL)
        {
            previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f l\n", previous_point.x, I.H-previous_point.y, current->suiv->data.x, I.H-current->suiv->data.y);
            current = current->suiv;
        }

        fprintf(f, "\n0 setlinewidth\ns\n");

        fprintf(f,"closepath\n\n");
        
    }

    else if (mode >= 3) // Mode Remplissage
    {

        fprintf(f, "%.1f %.1f m %.1f %.1f l\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y);

        Point previous_point;

        while (current->suiv != NULL)
        {
            previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f l\n", previous_point.x, I.H-previous_point.y, current->suiv->data.x, I.H-current->suiv->data.y);
            current = current->suiv;
        }

       // fprintf(f, "\n\nf\n");
       // fprintf(f,"closepath\n\n");
    }
}

void convert_to_EPS_cubic(Contour C, int mode, Image I, FILE* f)
{
    // Traite le cas où le contour est vide
    if (C.taille == 0)
    {
        fprintf(stderr, "Le Contour est vide !\n");
        return;
    }

    // Traite le cas où le nombre de points du contour
    // n'est pas multiple de 4

    if (C.taille % 4 != 0)
    {
        fprintf(stderr, "Le Contour ne contient pas le bon nombre de points !\n");
        return;   
    }

    // Cellule d'itération
    Cellule_Liste_Point* current = C.first->suiv->suiv->suiv->suiv; 

    if (mode == 1) // Mode contour avec segments
    {
        fprintf(f,"newpath\n");

        fprintf(f, "%.1f %.1f m %.1f %.1f %.1f %.1f %.1f %.1f c\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y, C.first->suiv->suiv->data.x, I.H-C.first->suiv->suiv->data.y, C.first->suiv->suiv->suiv->data.x, I.H-C.first->suiv->suiv->suiv->data.y);

        //Point previous_point;

        while (current != NULL)
        {
            //previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f %.1f %.1f %.1f %.1f c\n", current->data.x, I.H-current->data.y, current->suiv->data.x, I.H-current->suiv->data.y, current->suiv->suiv->data.x, I.H-current->suiv->suiv->data.y, current->suiv->suiv->suiv->data.x, I.H-current->suiv->suiv->suiv->data.y);
            current = current->suiv->suiv->suiv->suiv;
        }

        fprintf(f, "\n0 setlinewidth\ns\n");

        fprintf(f,"closepath\n");
    }

    else if (mode == 2) // Mode segments + points
    {   

        // Ci-dessous, l'affichage se fait en 2 étapes :
        // 1ère étape : on affiche les segments
        // 2ème étape en affiche les points
        // Compléxité : O(n+n) = O(2n) = O(n)

        // On commence d'abord par les points

        fprintf(f,"newpath\n");

        current = C.first;

        while (current != NULL)
        {
            fprintf(f, "\nnewpath\n%.1f %.1f 0.3 0 360 arc\nfill\nclosepath\n", current->data.x, I.H-current->data.y);
//            fprintf(f, "\nnewpath\n%.1f %.1f 0.3 0 360 arc\nfill\nclosepath\n", current->suiv->suiv->data.x, I.H-current->suiv->suiv->data.y);
            current = current->suiv->suiv->suiv->suiv;
        }

        current = C.first->suiv->suiv->suiv->suiv;

        // Après on remet l'itérateur current à la position initiale
        // et on parcours encore une fois la liste pour afficher les segments

       fprintf(f, "%.1f %.1f m %.1f %.1f %.1f %.1f %.1f %.1f c\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y, C.first->suiv->suiv->data.x, I.H-C.first->suiv->suiv->data.y, C.first->suiv->suiv->suiv->data.x, I.H-C.first->suiv->suiv->suiv->data.y);


        while (current != NULL)
        {
            fprintf(f, "%.1f %.1f l %.1f %.1f %.1f %.1f %.1f %.1f c\n", current->data.x, I.H-current->data.y, current->suiv->data.x, I.H-current->suiv->data.y, current->suiv->suiv->data.x, I.H-current->suiv->suiv->data.y, current->suiv->suiv->suiv->data.x, I.H-current->suiv->suiv->suiv->data.y);
            current = current->suiv->suiv->suiv->suiv;
        }

        fprintf(f, "\n0 setlinewidth\ns\n");

        fprintf(f,"closepath\n\n");
        
    }

    else if (mode >= 3) // Mode Remplissage
    {

        fprintf(f, "%.1f %.1f m %.1f %.1f %.1f %.1f %.1f %.1f c\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y, C.first->suiv->suiv->data.x, I.H-C.first->suiv->suiv->data.y, C.first->suiv->suiv->suiv->data.x, I.H-C.first->suiv->suiv->suiv->data.y);

        //Point previous_point;

        while (current != NULL)
        {
            //previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f %.1f %.1f %.1f %.1f c\n", current->data.x, I.H-current->data.y, current->suiv->data.x, I.H-current->suiv->data.y, current->suiv->suiv->data.x, I.H-current->suiv->suiv->data.y, current->suiv->suiv->suiv->data.x, I.H-current->suiv->suiv->suiv->data.y);
            current = current->suiv->suiv->suiv->suiv;
        }
    }
}

