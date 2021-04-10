#include <stdio.h>
#include "simplification_contour.h"

#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define reset "\e[0m"


int main(int argc, char** argv)
{
    if (argc != 1)
    {
        fprintf(stderr,"Usage : ./test_simplification_contour_bezier\n");
        return -1;
    }

    int n;
    printf("Donnez un entier n : \n");
    scanf("%d",&n);

    if (n <= 0)
    {
        fprintf(stderr, "[ERR] : n doit être un entier positif et non-nul\n");
        return -1;
    }

    Contour C = creer_liste_Point_vide();

    // Test (a)

    double x,y;
    Point P;
    Tableau_Point T;
    Bezier2 B2_approx;

if (n == 1)
{
    for (int i = 0 ; i < 2 ; i++)
    {
        printf("Donnez vos points (abscisse puis ordonné)\n");
        scanf("%lf" ,&x);
        scanf("%lf", &y);
        P = set_point(x,y);
        ajouter_element_liste_Point(&C, P);
    }

    T = sequence_points_liste_vers_tableau(C);

    B2_approx = approx_bezier2(C, 0, C.taille-1);

    P = mult_Point(0.5,add_point(T.tab[0],T.tab[1]));
    
    if (!(distance(T.tab[0],B2_approx.C0)
        && distance(B2_approx.C1, P)
        && distance(T.tab[1],B2_approx.C2)))
    {
        printf(GRN "BON\n" reset);
    }

    printf("== Contour : ==\n");
    afficher_point(T.tab[0]);
    afficher_point(P);
    afficher_point(T.tab[1]);

    printf("== POINTS DE CONTROLES (COURBE DE BEZIER 2 APPROX.) : ==\n");
    afficher_point(B2_approx.C0);
    afficher_point(B2_approx.C1);
    afficher_point(B2_approx.C2);

    C = creer_liste_Point_vide();
}
else
{
    // TEST (b)

    Bezier2 B2;

    for (int i = 0 ; i <= 2 ; i++)
    {
        printf("Donnez vos points (abscisse puis ordonné)\n");
        scanf("%lf" ,&x);
        scanf("%lf", &y);
        P = set_point(x,y);
        ajouter_element_liste_Point(&C, P);
    }

    T = sequence_points_liste_vers_tableau(C);

    B2.C0 = T.tab[0];
    B2.C1 = T.tab[1];
    B2.C2 = T.tab[2];

    C = creer_liste_Point_vide();
    
    for (int i = 0 ; i <= n ; i++)
    {
        P = BEZIER_2(B2, i / (double)n);
        ajouter_element_liste_Point(&C, P);
    }

    printf("== POINTS DE CONTROLES (COURBE DE BEZIER 2) : ==\n");
    afficher_point(B2.C0);
    afficher_point(B2.C1);
    afficher_point(B2.C2);

    B2_approx = approx_bezier2(C, 0, C.taille-1);

    printf("== POINTS DE CONTROLES (COURBE DE BEZIER 2 APPROX.) : ==\n");
    afficher_point(B2_approx.C0);
    afficher_point(B2_approx.C1);
    afficher_point(B2_approx.C2);

    if (!(distance(B2.C0, B2_approx.C0)
        && distance(B2.C1, B2_approx.C1)
        && distance(B2.C2, B2_approx.C2)))
    {
        printf(GRN "BON\n" reset);
    }
    

    C = creer_liste_Point_vide();
}
    // TEST (c):   
    printf(RED "\n\n\nTEST C :\n\n\n" reset);
    Point Q0 = set_point(0,0);
    Point Q1 = set_point(1,0);
    Point Q2 = set_point(1,1);
    Point Q3 = set_point(1,2);
    Point Q4 = set_point(2,2);
    Point Q5 = set_point(3,2);
    Point Q6 = set_point(3,3);
    Point Q7 = set_point(4,3);
    Point Q8 = set_point(5,3);

    ajouter_element_liste_Point(&C, Q0);
    ajouter_element_liste_Point(&C, Q1);
    ajouter_element_liste_Point(&C, Q2);
    ajouter_element_liste_Point(&C, Q3);
    ajouter_element_liste_Point(&C, Q4);
    ajouter_element_liste_Point(&C, Q5);
    ajouter_element_liste_Point(&C, Q6);
    ajouter_element_liste_Point(&C, Q7);
    ajouter_element_liste_Point(&C, Q8);

    
    printf("== CONTOUR : ==\n");
    ecrire_contour(C);

    B2_approx = approx_bezier2(C, 0, C.taille-1);

    printf("== POINTS DE CONTROLES (COURBE DE BEZIER 2 APPROX.) : ==\n");
    afficher_point(B2_approx.C0);
    afficher_point(B2_approx.C1);
    printf(GRN"BON\n"reset);
    afficher_point(B2_approx.C2);

}