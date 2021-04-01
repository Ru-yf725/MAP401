#include <stdio.h>
#include "simplification_contour.h"

void afficher_tableau(Tableau_Point T)
{
	for (int i = 0 ; i < T.taille ; i++)
	{
		afficher_point(T.tab[i]);
	}
}

void vider_tableau(Tableau_Point* T)
{
	Point P = {-1,-1};
	for (int i = 0 ; i < T->taille ; i++)
	{
		T->tab[i] = P;
	}
	T->taille = 0;
}

void convert_to_EPS_(Contour C, int mode, Image I, FILE* f)
{
    if (C.taille == 0)
    {
        fprintf(stderr, "Le Contour est vide !\n");
        return;
    }

    // Cellule d'itération
    Cellule_Liste_Point* current = C.first->suiv; 

    if (mode == 1) // Mode contour avec segments
    {
        fprintf(f,"newpath\n");

        fprintf(f, "%.1f %.1f m %.1f %.1f l\n", C.first->data.x, I.H-C.first->data.y, C.first->suiv->data.x, I.H-C.first->suiv->data.y);

        Point previous_point;

        while (current->suiv != NULL)
        {
            previous_point = current->data;
            fprintf(f, "%.1f %.1f l %.1f %.1f l\n", previous_point.x, I.H-previous_point.y, current->suiv->data.x, I.H-current->suiv->data.y);
            current = current->suiv;
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
    }
}

Bezier2 approx_bezier2(Contour C, double n)
{

  Tableau_Point T = sequence_points_liste_vers_tableau(C);

  Bezier2 B2;

  B2.C0 = T.tab[0];
  B2.C2 = T.tab[C.taille-1];

//  B2.C1 = set_point(0,0);

  if (n == 1)
  {
    B2.C1 = add_point(T.tab[0],T.tab[C.taille-1]);
    B2.C1 = mult_Point(0.5,B2.C1);
  }

  else if (n >= 2)
  {

    double alpha = 3*n/(n*n-1);

    double beta = (1-2*n)/(2*(n+1));

    //printf("(alpha,beta) = (%lf, %lf)\n", alpha, beta);
    
    // Aux : Auxilary Point
    Point Aux = add_point(T.tab[0],T.tab[C.taille-1]); 

    Aux = mult_Point(beta, Aux);

    for (int i = 1 ; i <= (int)n-1 ; i++)
    {
        B2.C1 = add_point(B2.C1,T.tab[i]);
    }

    B2.C1 = mult_Point(alpha, B2.C1);

    B2.C1 = add_point(B2.C1, Aux);

  }

  return B2;
}

/*Contour contour_poly(Contour C)
{
    Tableau_Point P = sequence_points_liste_vers_tableau(C);   

}*/

Point BEZIER_2(Bezier2 B, double t)
{
    return (add_point(add_point(
            mult_Point((1-t)*(1-t),B.C0),
            mult_Point(2*t*(1-t),B.C1)),
            mult_Point(t*t, B.C2)));
}

/*Point BEZIER_3(Contour C, double t)
{
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    
    return ;
}*/

int main(int argc, char** argv)
{

    Contour C = creer_liste_Point_vide();

    // Initialise les points 
    Point Q0 = set_point(2,1);
    Point Q1 = set_point(1,1);
    Point Q2 = set_point(3,0);

    Bezier2 B = add_bezier_2(Q0, Q1, Q2);

    // Ajout des points Q0, Q1, Q2 à B2 (Bezier de degré 2)
    Point P;
    Bezier2 B2_approx;

    /*int n;
    scanf("%d", &n);*/
    int n = 5;
    
    if (n == 1)
    {
        ajouter_element_liste_Point(&C,Q0);
        ajouter_element_liste_Point(&C,Q1);
        B2_approx = approx_bezier2(C,n);


        printf("== CONTOUR POLYGONAL : ==\n");
        ecrire_contour(C);

        printf("== COURBE DE BEZIER 2 : ==\n");
        afficher_point(B2_approx.C0);
        afficher_point(B2_approx.C1);
        afficher_point(B2_approx.C2);
    }
    else if (n >= 2)
    {
    // 
    for (int i = 0 ; i <= n ; i++)
    {
        P = BEZIER_2(B, i / (double)n);
        ajouter_element_liste_Point(&C, P);
    }

    ecrire_contour(C);

    B2_approx = approx_bezier2(C,n); // Courbe calculée

    printf("== CONTOUR POLYGONAL : ==\n");
    afficher_point(B.C0);
    afficher_point(B.C1);
    afficher_point(B.C2);

    //ecrire_contour(C);

    printf("== COURBE DE BEZIER 2 : ==\n");
    afficher_point(B2_approx.C0);
    afficher_point(B2_approx.C1);
    afficher_point(B2_approx.C2);
    

    int d;
    Image I;
    Contour C;
    Robot R;
    Tableau_Point T;
    Contour L;

    I = lire_fichier_image(argv[1]);

    sscanf(argv[2], "%d", &d);

    Image M = mask_detection(I);
    

    Point PM = trouver_pixel_depart(M);
    Point P0;

    FILE* f = fopen("contour_simplifie_sortie.eps","w");

    // Headers du fichier EPS 
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n");


    do {

        C = creer_liste_Point_vide();

        det_contour(I, &M, P0, &R, &C);


        PM = trouver_pixel_depart(M);

        T = sequence_points_liste_vers_tableau(C);

        L = simplification_douglas_peucker(T,0,C.taille-1,d);

        ajouter_element_liste_Point(&L, L.first->data);

        ecrire_contour(L);

        convert_to_EPS_(L, 3, I, f);

        } while (PM.x != -1 && PM.y != -1);


    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);  

    }
}

/*int main(int argc, char** argv)
{
	int d;
	Image I;
	Contour C;
	Robot R;
	Tableau_Point T;
	Contour L;

	I = lire_fichier_image(argv[1]);

	sscanf(argv[2], "%d", &d);

	Image M = mask_detection(I);
	

	Point PM = trouver_pixel_depart(M);
	Point P0;

	FILE* f = fopen("contour_simplifie_sortie.eps","w");

	// Headers du fichier EPS 
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n");

    int nombre_contours = 0;
    int somme_segments_total = 0;
    int somme_segments_simpli = 0;
    int nombre_de_points = 0;


	do {

		C = creer_liste_Point_vide();

		det_contour(I, &M, P0, &R, &C);

		++nombre_contours;
		somme_segments_total += C.taille-1;
		nombre_de_points += C.taille;

        PM = trouver_pixel_depart(M);

        T = sequence_points_liste_vers_tableau(C);

        L = simplification_douglas_peucker(T,0,C.taille-1,d);

        ajouter_element_liste_Point(&L, L.first->data);

        somme_segments_simpli += L.taille-1;

        ecrire_contour(L);

        convert_to_EPS_(L, 3, I, f);

 		//sauvegarder_contour(f_con, L);

    	} while (PM.x != -1 && PM.y != -1);


    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);

    printf("nombre de segments : %d\n", somme_segments_total);
    printf("nombre de contours : %d\n", nombre_contours);
    //printf("nombre de points : %d\n", nombre_de_points);
    printf("nombre de segments après simplification : %d\n", somme_segments_simpli);

}*/