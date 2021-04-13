#include <stdio.h>
#include "simplification_contour.h"

int main(int argc, char** argv)
{
    // Test (a)
/*
//    int n = 1;

    Contour C;

    Point P0 = set_point(1,2);
    Point P1 = set_point(1,1);

    // Création du contour polygonal
    C = creer_liste_Point_vide();

    // Ajout des points P0 et P1
    ajouter_element_liste_Point(&C, P0);
    ajouter_element_liste_Point(&C, P1);

    // appel à la fonction approx_bezier3
    Bezier3 B3 = approx_bezier3(C,0, C.taille-1);

    printf("=== Points de controles ===\n");
    afficher_point(B3.C0);
    afficher_point(B3.C1);
    afficher_point(B3.C2);
    afficher_point(B3.C3);

    printf("=== Contour ===\n");
    ecrire_contour(C);

*/
    //Test (b)
/*
    int n = 2;

    Contour C = creer_liste_Point_vide(); // On vide le contour C

    Point P0 = set_point(1,2);
    Point P1 = set_point(1,1);
    Point P2 = set_point(3,1);

    ajouter_element_liste_Point(&C, P0);
    ajouter_element_liste_Point(&C, P1);
    ajouter_element_liste_Point(&C, P2);

    Bezier3 B3 = approx_bezier3(C,0, C.taille-1);

    printf("=== Points de controles ===\n");
    afficher_point(B3.C0);
    afficher_point(B3.C1);
    afficher_point(B3.C2);
    afficher_point(B3.C3);

    printf("=== Contour ===\n");
    ecrire_contour(C);
*/
/*
    int n = 4;

    Contour C = creer_liste_Point_vide(); // On vide le contour C

    Point Q0 = set_point(1,2);
    Point Q1 = set_point(1,1);
    Point Q2 = set_point(3,1);
    Point Q3 = set_point(2,2);

    Bezier3 B3;
    B3.C0 = Q0;
    B3.C1 = Q1;
    B3.C2 = Q2;
    B3.C3 = Q3;

    for (int i = 0 ; i <= n ; i++)
    {
        ajouter_element_liste_Point(&C, BEZIER_3(B3,i/(double)n));
    }

    Bezier3 B3_approx = approx_bezier3(C,0, C.taille-1);

    printf("=== Points de controles de la Bezier 3 ===\n");
    afficher_point(B3.C0);
    afficher_point(B3.C1);
    afficher_point(B3.C2);
    afficher_point(B3.C3);

    printf("=== Points de controles de la Bezier 3 approximée ===\n");
    afficher_point(B3_approx.C0);
    afficher_point(B3_approx.C1);
    afficher_point(B3_approx.C2);
    afficher_point(B3_approx.C3);
*/
    int n = 8;

    Contour C;

    Point P0 = set_point(0,0);
    Point P1 = set_point(1,0);
    Point P2 = set_point(1,1);
    Point P3 = set_point(1,2);
    Point P4 = set_point(2,2);
    Point P5 = set_point(3,2);
    Point P6 = set_point(3,3);
    Point P7 = set_point(4,3);
    Point P8 = set_point(5,3);

    // Création du contour polygonal
    C = creer_liste_Point_vide();

    // Ajout des points P0 et P1
    ajouter_element_liste_Point(&C, P0);
    ajouter_element_liste_Point(&C, P1);
    ajouter_element_liste_Point(&C, P2);
    ajouter_element_liste_Point(&C, P3);
    ajouter_element_liste_Point(&C, P4);
    ajouter_element_liste_Point(&C, P5);
    ajouter_element_liste_Point(&C, P6);
    ajouter_element_liste_Point(&C, P7);
    ajouter_element_liste_Point(&C, P8);

    // appel à la fonction approx_bezier3
    Bezier3 B3 = approx_bezier3(C,0, C.taille-1);

    printf("=== Points de controles ===\n");
    afficher_point(B3.C0);
    afficher_point(B3.C1);
    afficher_point(B3.C2);
    afficher_point(B3.C3);

    printf("=== Contour ===\n");
    ecrire_contour(C);

}