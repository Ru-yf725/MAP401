#include <stdio.h>
#include "simplification_contour.h"
#include "bezier.h"

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

       // fprintf(f, "\n\nf\n");
       // fprintf(f,"closepath\n\n");
    }
}

int main(int argc, char** argv)
{
   
    int d;
    Image I;
    Contour C;
    Robot R;
    Tableau_Point T;
    Contour L;
    Bezier2 B;

    I = lire_fichier_image(argv[1]);

    sscanf(argv[2], "%d", &d);

    Image M = mask_detection(I);
    
    Point PM = trouver_pixel_depart(M);
    Point P0;

    FILE* f = fopen("contour_simplifie_sortie.eps","w");
    FILE* f_con = fopen("contour.txt.contours","w");

    // Headers du fichier EPS 
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n");

    int nombre_contours = 0;
    int nombre_courbes = 0;

   // do {

        C = creer_liste_Point_vide();

        /*Point Q0 = set_point(0,0);
        Point Q1 = set_point(1,0);
        Point Q2 = set_point(1,1);
        Point Q3 = set_point(1,2);
        Point Q4 = set_point(2,2);
        Point Q5 = set_point(3,2);
        Point Q6 = set_point(3,3);
        Point Q7 = set_point(4,3);
        Point Q8 = set_point(5,3);*/

        det_contour(I, &M, P0, &R, &C);
        // Quand on arrive ici, le contour C est rempli

        /*ajouter_element_liste_Point(&C, Q0);
        ajouter_element_liste_Point(&C, Q1);
        ajouter_element_liste_Point(&C, Q2);
        ajouter_element_liste_Point(&C, Q3);
        ajouter_element_liste_Point(&C, Q4);
        ajouter_element_liste_Point(&C, Q5);
        ajouter_element_liste_Point(&C, Q6);
        ajouter_element_liste_Point(&C, Q7);
        ajouter_element_liste_Point(&C, Q8);*/

        ecrire_contour(C);

        ++nombre_contours;
        //

        PM = trouver_pixel_depart(M);

        T = sequence_points_liste_vers_tableau(C);

        //printf("->");
        //afficher_point(T.tab[C.taille-1]);

        L = simplification_douglas_peucker_bezier2(C,0,C.taille-1,d);

        ajouter_element_liste_Point(&L, L.first->data);
        
        ecrire_contour(L);

        convert_to_EPS_(L, 1, I, f);

        //sauvegarder_contour(f_con, L);

  //      } while (PM.x != -1 && PM.y != -1);

    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);

    //printf("nombre de segments : %d\n", somme_segments_total);
    printf("nombre de courbes : %d\n", nombre_courbes);
    //printf("nombre de points : %d\n", nombre_de_points);
    //printf("nombre de segments après simplification : %d\n", somme_segments_simpli);


/*
    //Contour C = creer_liste_Point_vide();

    // Initialise les points 
    
    Point Q0 = set_point(0,0);
    Point Q1 = set_point(1,0);
    Point Q2 = set_point(1,1);
    Point Q3 = set_point(1,2);
    Point Q4 = set_point(2,2);
    Point Q5 = set_point(3,2);
    Point Q6 = set_point(3,3);
    Point Q7 = set_point(4,3);
    Point Q8 = set_point(5,3);
    

    //B = add_bezier_2(Q0, Q1, Q2);    

    Contour C = creer_liste_Point_vide();

    ajouter_element_liste_Point(&C, Q0);
    ajouter_element_liste_Point(&C, Q1);
    ajouter_element_liste_Point(&C, Q2);
    ajouter_element_liste_Point(&C, Q3);
    ajouter_element_liste_Point(&C, Q4);
    ajouter_element_liste_Point(&C, Q5);
    ajouter_element_liste_Point(&C, Q6);
    ajouter_element_liste_Point(&C, Q7);
    ajouter_element_liste_Point(&C, Q8);

    Tableau_Point T = sequence_points_liste_vers_tableau(C);

    Point P;
    Bezier2 B2_approx;

    int n = C.taille-1;

    B2_approx = approx_bezier2(C, 0, C.taille-1);
    
    if (n == 1)
    {
        ajouter_element_liste_Point(&C,T.tab[0]);
        ajouter_element_liste_Point(&C,T.tab[1]);


        printf("== CONTOUR POLYGONAL : ==\n");
        ecrire_contour(C);

        printf("== COURBE DE BEZIER 2 : ==\n");
        afficher_point(B2_approx.C0);
        afficher_point(B2_approx.C1);
        afficher_point(B2_approx.C2);
    }
    else if (n >= 2)
    {
    
    for (int i = 0 ; i <= n ; i++)
    {
        P = BEZIER_2(B2_approx, i / (double)n);
        ajouter_element_liste_Point(&C, P);
    }

    //B2_approx = approx_bezier2(C,0,C.taille-1); // Courbe calculée

    printf("== BEZIER 2 : ==\n");
    //afficher_point(B.C0);
    //afficher_point(B.C1);
    //afficher_point(B.C2);

    ecrire_contour(C);

    printf("== COURBE DE BEZIER 2 : ==\n");
    afficher_point(B2_approx.C0);
    afficher_point(B2_approx.C1);
    afficher_point(B2_approx.C2);
    }
    */
    
    /*

    Point Q0 = set_point(0,0);
    Point Q1 = set_point(1,0);
    Point Q2 = set_point(1,1);
    Point Q3 = set_point(1,2);
    Point Q4 = set_point(2,2);
    Point Q5 = set_point(3,2);
    Point Q6 = set_point(3,3);
    Point Q7 = set_point(4,3);
    Point Q8 = set_point(5,3);

    Contour C = creer_liste_Point_vide();
    ajouter_element_liste_Point(&C, Q0);
    ajouter_element_liste_Point(&C, Q1);
    ajouter_element_liste_Point(&C, Q2);
    ajouter_element_liste_Point(&C, Q3);
    ajouter_element_liste_Point(&C, Q4);
    ajouter_element_liste_Point(&C, Q5);
    ajouter_element_liste_Point(&C, Q6);
    ajouter_element_liste_Point(&C, Q7);
    ajouter_element_liste_Point(&C, Q8);

    Bezier2 B2_approx = approx_bezier2(C, 0, C.taille-1);
    afficher_point(B2_approx.C1);
    */

}