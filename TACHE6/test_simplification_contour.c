#include <stdio.h>
#include "simplification_contour.h"

void afficher_tableau(Tableau_Point T)
{
	for (int i = 0 ; i < T.taille ; i++)
	{
		afficher_point(T.tab[i]);
	}
}

void init_tableau(Tableau_Point* T)
{
	Point P = {0,0};

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
    Cellule_Liste_Point* current = C.first; 

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
	Liste_Point C;
	Robot R;
	Tableau_Point T;
	Liste_Point L;

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

//	do {
for (int k = 0 ; k < 2 ; k++)
{
        det_contour(I, &M, P0, &R, &C);

        PM = trouver_pixel_depart(M);

        //printf("== CONTOURS : == \n\n");
        //ecrire_contour(C);
        T = sequence_points_liste_vers_tableau(C);
        //printf("== TABLEAU : == \n\n");
        //afficher_tableau(T);
        L = simplification_douglas_peucker(T,0,1500,d);
        //printf("== CONTOUR L : == \n\n");
        ecrire_contour(L);

 		//sauvegarder_contour(f, L);

    //	} while (PM.x != -1 && PM.y != -1);
}

convert_to_EPS_(L, 1, I, f);

    fprintf(f, "\nf\n");
    fprintf(f, "\nclosepath");
    fprintf(f, "\nshowpage\n");

    fclose(f);

}
