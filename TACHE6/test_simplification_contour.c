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

       // fprintf(f, "\n\nf\n");
       // fprintf(f,"closepath\n\n");
    }
}


int main(int argc, char** argv)
{
        if (argc != 3)
        {
          printf("Usage: ./test_simplification [IMAGE] [d]\n");
          return -1;
        }

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

	/* Headers du fichier EPS */
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

//        ecrire_contour(L);

        convert_to_EPS_(L, 3, I, f);

 		//sauvegarder_contour(f_con, L);

    	} while (PM.x != -1 && PM.y != -1);


    fprintf(f, "\nf\n");
    fprintf(f, "\nshowpage\n");
    fclose(f);

    printf("Fichier : %s\n", argv[1]);
    printf("nombre de segments : %d\n", somme_segments_total);
    printf("nombre de contours : %d\n", nombre_contours);
    printf("d = %d\n", d);
    printf("nombre de segments après simplification : %d\n", somme_segments_simpli);

}
