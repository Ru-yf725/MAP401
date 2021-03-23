#include <stdio.h>
#include <string.h>
#include "contour.h"

void init_robot(Point P, Robot* R)
{
    R->x = P.x;
    R->y = P.y;
    R->O = EST;
}


Point trouver_pixel_depart(Image I)
{
    Point P = {-1,-1};

    for (UINT i = 1; i <= I.H; i++)
    {
        for (UINT j = 1; j <= I.L; j++)
        {
            if (get_pixel_image(I,j,i) == NOIR && get_pixel_image(I,j,i-1) == BLANC)
            {
                P.x = (double) j;
                P.y = (double) i;
                return P;
            }
        }
    }
    // Si on arrive ici ça veut dire qu'on a pas trouvé de pixel noir
    // avec un pixel blanc au dessus donc on retourne le point (-1,-1)
    // Comme indication d'erreur

    //printf("[ERREUR]: Aucun pixel noir avec un pixel blanc au dessus n'a été trouvé");
    return P;
}


void avancer(Robot *R)
{
    switch (R->O)
    {
    case NORD:
        R->y--;
        break;
    case OUEST:
        R->x--;
        break;
    case SUD:
        R->y++;
        break;
    case EST:
        R->x++;
        break;
    default:
        ERREUR_FATALE("[ERREUR]: Mauvaise Orientation")
        break;
    }
}


void tourner_a_droite(Robot *R)
{
    switch (R->O)
    {
      case NORD:
        R->O = EST;
        break;
      case EST:
        R->O = SUD;
        break;
      case SUD:
        R->O = OUEST;
        break;
      case OUEST:
        R->O = NORD;
        break;
    }
}


void tourner_a_gauche(Robot* R)
{
    switch (R->O)
    {
      case NORD:
        R->O = OUEST;
        break;
      case EST:
        R->O = NORD;
        break;
      case OUEST:
        R->O = SUD;
        break;
      case SUD:
        R->O = EST;
        break;
    }
}


void nouvelle_orientation(Robot* R, Image I)
{
    Pixel pG, pD;
    pixel_devant_robot(*R, I, &pG, &pD);

    if (pG == BLANC && pD == BLANC)
    {
        tourner_a_droite(R);
        return;
    }

    if (pG == BLANC && pD == NOIR)
    {
        return;
    }

    if (pG == NOIR && pD == BLANC)
    {
        tourner_a_gauche(R);
        return;
    }

    if (pG == NOIR && pD == NOIR)
    {
        tourner_a_gauche(R);
        return;
    }
}

void memoriser_position(Robot R, Liste_Point* L, Point P)
{
    printf("(%.1f ; %.1f)\n", R.x , R.y);
    ajouter_element_liste_Point(L, P);
}

void pixel_devant_robot(Robot R, Image I, Pixel *pG, Pixel *pD)
{
    switch (R.O)
    {
        case NORD:
            *pG = get_pixel_image(I, R.x, R.y);
            *pD = get_pixel_image(I, R.x+1, R.y);
            break;
        case SUD:
            *pG = get_pixel_image(I, R.x+1, R.y+1);
            *pD = get_pixel_image(I, R.x, R.y+1);
            break;
        case OUEST:
            *pG = get_pixel_image(I, R.x, R.y+1);
            *pD = get_pixel_image(I, R.x, R.y);
            break;
        case EST:
            *pG = get_pixel_image(I, R.x+1, R.y);
            *pD = get_pixel_image(I, R.x+1, R.y+1);
            break;
        
    default:
        break;
    }
}

void sauvegarder_contour(FILE* f, Contour C)
{
    fprintf(f, "\n");
    fprintf(f, "\n\n%d\n",C.taille);

    Cellule_Liste_Point* current = C.first;

    while (current != NULL)
    {
      fprintf(f, " %.1f %.1f \n",current->data.x,current->data.y);
      current = current->suiv;
    }
}

void convert_to_EPS(Contour C, int mode, Image I, FILE* f)
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

Image mask_detection(Image I)
{

    Image M = creer_image(I.L,I.H);

    for (int i = 1 ; i <= I.H ; i++)
    {
        for (int j = 1 ; j <= I.L ; j++)
        {
            if (get_pixel_image(I,j,i) == NOIR && get_pixel_image(I,j,i-1) == BLANC)
            {
                M.tab[j-1+I.L*(i-1)] = NOIR;
            }
            else
            {
                M.tab[j-1+I.L*(i-1)] = BLANC;
            }
        }
    }
    return M;
}

void det_contour(Image I, Image* M, Point P0, Robot* R, Contour* C)
{
    P0 = trouver_pixel_depart(*M);

    P0.x--;
    P0.y--;
    
    init_robot(P0,R);
    
    Point P_current; // Point courant

    do {

        P_current.x = R->x;
        P_current.y = R->y;

        memoriser_position(*R, C, P_current);
        if (R->O == EST)
        {
            M->tab[(int)(P_current.x)+I.L*((int)(P_current.y))] = BLANC;
        }
        avancer(R);
        nouvelle_orientation(R, I);
        
    } while(!( (R->x == P0.x) && (R->y == P0.y) && (R->O == EST) ));
    memoriser_position(*R, C, P0);
    printf("\n");
}
