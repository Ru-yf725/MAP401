#include <stdio.h>
#include "simplification_contour.h"

/* Programme de TEST pour la simplification d'une image par segments */
int main(int argc, char** argv)
{
    // Données
	double d;
	Image I;
	Contour C;
	Robot R;
	Tableau_Point T;
	Contour L;

    // Lecture image
	I = lire_fichier_image(argv[1]);

    // Récupération de la valeur distance-seuil d depuis l'arg
	sscanf(argv[2], "%lf", &d);

    // Detection du MASK
	Image M = mask_detection(I);
	
    // Trouver le point de départ
	Point PM = trouver_pixel_depart(M);
	Point P0;

    // ouverture du fichier .eps en mode write
	FILE* f = fopen("contour_simplifie_sortie.eps","w");

    // Initialisation des variables compteurs
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

        //ecrire_contour(L);

        convert_to_EPS(L, 3, I, f);

 	    //sauvegarder_contour(f_con, L);

    	} while (PM.x != -1 && PM.y != -1);




    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);

    printf("\n\nFichier : %s\n", argv[1]);
    printf("nombre de segments : %d\n", somme_segments_total);
    printf("nombre de contours : %d\n", nombre_contours);
    printf("d = %lf\n", d);
    printf("nombre de segments après simplification : %d\n", somme_segments_simpli);

}
