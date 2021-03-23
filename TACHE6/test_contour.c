#include "contour.h"
#include "image.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "[USAGE] : ./test_contour exemple_image.pbm exemple_image.contours\n");
		return -1;
	}

	Liste_Point C;

	Image I;
	Robot R;

    I = lire_fichier_image(argv[1]);

    // On determine le mask et on le stock dans le type image M
    Image M = mask_detection(I); 

    Point PM = trouver_pixel_depart(M); //Pixel départ de Mask
    Point P0; // Point initial pour I

    int nombre_contours = 0;
    int somme_segments = 0;
    int nombre_de_points = 0;

    printf("== CONTOURS TROUVES ==\n");

    FILE* f_eps = fopen("sortie.eps","w");

    /* Headers du fichier EPS */
    fprintf(f_eps, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f_eps, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f_eps, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n");

    char txt[40];
    strcat(txt, argv[1]);
    strcat(txt, ".contours");

    FILE* f_contour = fopen(txt,"w");

    /* Tant qu'il existe un pixel noir dans l'image mask */
    do {
        det_contour(I, &M, P0, &R, &C);

        somme_segments += C.taille-1;
        PM = trouver_pixel_depart(M);
        nombre_de_points += C.taille;

        convert_to_EPS(C, 3, I, f_eps);

        sauvegarder_contour(f_contour,C);

        printf("== CONTOURS : == \n\n");
        ecrire_contour(C);
        supprimer_liste_Point(C);
        C = creer_liste_Point_vide();
        nombre_contours++;
    } while (PM.x != -1 && PM.y != -1);

    fprintf(f_eps, "\nf\n");
    fprintf(f_eps, "\nclosepath");


    rewind(f_contour); // Ici on remet le FILE stream en position initial

    // On écrit le nombre de contours au début du fichier .txt
    // Pour éviter de parcourir la liste 2 fois
    fprintf(f_contour, "%d\n", nombre_contours); 

    fprintf(f_eps, "\nshowpage\n");

    /* Et on ferme les streams */
    fclose(f_eps);
    fclose(f_contour);

    /* Affichage des détails obtenus */
    printf("Nombre de contours : %d\n", nombre_contours);
    printf("Somme de segments : %d\n", somme_segments);
    printf("Nombre de points : %d\n", nombre_de_points);


    /* Ci-dessous la partie ecriture dans le fichier *.contours (de sortie) */

    sauvegarder_contour(f_contour, C);
    
    /* Sortie format EPS selon le mode choisi */

    //convert_to_EPS(C, 3, I, f_eps);

    printf("\n> Sortie [.txt] enregistrée sous le nom \"%s\"\n", txt);

    printf("Fichier PostScript enregistré sous le nom \"%s\"\n", "sortie.eps");

}

