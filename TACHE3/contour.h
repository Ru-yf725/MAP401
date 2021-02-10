#ifndef _CONTOUR_IMAGE_H_
#define _CONTOUR_IMAGE_H_

#include "image.h"
#include "sequence_point.h"

typedef enum {NORD, EST, SUD, OUEST} Orientation;

typedef struct Robot_
{

  Orientation O;
  double x,y;

} Robot;

/*crée et intialise un robot*/
void init_robot(Point P, Robot* R);

/* Fonction de recherche du pixel de départ */
Point trouver_pixel_depart(Image I);

/*Fonction du deplacement du robot*/
void avancer(Robot *r);

/* Tourne le robot a droite */
void tourner_a_droite(Robot *r);

/* Tourne le robot a gauche */
void tourner_a_gauche(Robot *r);

/*change l'orientation du robot */
void nouvelle_orientation(Robot *r, Image I);

/*Ecrit a l'ecran les positions successive du robot a stocker aussi en memoire */
void memoriser_position(Robot R, Liste_Point* L, Point P);

/* S'occupe de enregistrement des contours dans un fichier de sortie *.contours */
void sauvegarder_contour(char* nom_fichier_sortie, Contour C);

/* retourne les pixels avant gauche et avant droite du robot */
void pixel_devant_robot(Robot r, Image I, Pixel *a_g, Pixel *a_d);

#endif /* _CONTOUR_IMAGE_H_ */