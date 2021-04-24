#include <stdio.h>
#include "simplification_contour.h"

int main(int argc, char** argv)
{

    double d;
    Image I;
    Contour C;
    Robot R;
    Tableau_Point T;
    Contour L;

    I = lire_fichier_image(argv[1]);
	
    printf("\n\nFichier : %s\n",argv[1]);

    sscanf(argv[2], "%lf", &d);

    Image M = mask_detection(I);
    
    Point PM = trouver_pixel_depart(M);
    Point P0;

    FILE* f = fopen("contour_simplifie_sortie.eps","w");
    FILE* f_con = fopen("contour.txt.contours","w");

    // Headers du fichier EPS 
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f, "%c%cBoundingBox: 0 0 %u %u\n",'%','%', I.L, I.H);
    fprintf(f, "/l {lineto} def \n/m {moveto} def \n/s {stroke} def\n/f {fill} def\n/c {curveto} def\n");

    int nombre_contours = 0;
    int nombre_courbes = 0;

    do {

        C = creer_liste_Point_vide();

        det_contour(I, &M, P0, &R, &C);

        // Quand on arrive ici, le contour C est rempli

        ++nombre_contours;

        PM = trouver_pixel_depart(M);

        T = sequence_points_liste_vers_tableau(C);

        L = simplification_douglas_peucker_bezier3(T,0,C.taille-1,d);

        convert_to_EPS_cubic(L, 3, I, f);

        sauvegarder_contour(f_con, L);

        nombre_courbes += L.n;

        } while (PM.x != -1 && PM.y != -1);

    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);
    fclose(f_con);

    printf("Nombre de Courbes : %d\n", nombre_courbes);
    printf("Nombre de Contours : %d\n", nombre_contours);
    printf("d = %lf\n", d);
}
