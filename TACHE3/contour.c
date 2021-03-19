#include <stdio.h>
#include "contour.h"
#include "types_macros.h"

void init_robot(Point P, Robot* R)
{
    R->x = P.x;
    R->y = P.y;
    R->O = EST;
}


Point trouver_pixel_depart(Image I)
{

    Point P = {-1,-1};

    for (UINT i = 1; i < I.H; i++)
    {
        for (UINT j = 1; j < I.L; j++)
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
    printf("[ERREUR]: Aucun pixel noir avec un pixel blanc au dessus n'a été trouvé");
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


void tourner_a_gauche(Robot *R)
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
    
    if (pG == BLANC && pD == BLANC){
        tourner_a_droite(R);
        return;
    }

    if (pG == BLANC && pD == NOIR){
        return;
    }

    if (pG == NOIR && pD == BLANC){
        tourner_a_gauche(R);
        return;
    }

    if (pG == NOIR && pD == NOIR){
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

void sauvegarder_contour(char* nom_fichier_sortie, Contour C)
{
    printf("\n> Sortie enregistrée dans le fichier \"%s\"\n", nom_fichier_sortie);
    FILE* f = fopen(nom_fichier_sortie,"w");

    fprintf(f, "1\n\n");
    fprintf(f, "%d\n",C.taille);

    Cellule_Liste_Point* current = C.first;

    while (current != NULL)
    {
      fprintf(f, " %.1f %.1f \n",current->data.x,current->data.y);
      current = current->suiv;
    }

    fclose(f);
}
