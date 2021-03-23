#ifndef GEOM2D_
#define GEOM2D_

#include "sequence_point.h"

/* cree le point de coordonnées (x,y) */
Point set_point(double x, double y);

/* cree le vecteur de coordonnées (x,y) */
Vecteur set_vecteur(double x, double y);

/* Somme de P1+P2 */
Point add_point(Point P1, Point P2);

/* Soustraction P1-P2 */
Point soustraction_point(Point P1, Point P2);

/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B);

/* Retourne la distance entre deux points */
double distance(Point A, Point B);

/* Afficher le point donné en paramètre */
void afficher_point(Point P);

/* Afficher le vecteur donné en paramètre */
void afficher_vecteur(Vecteur V);

/* Soustraction de deux vecteurs */
Vecteur soustraction(Vecteur U, Vecteur V);

/* Multiplication d'un vecteur par un scalaire r */
Vecteur mult_scalaire(double r, Vecteur V);

/* Produit scalaire de 2 vecteurs */
double produit_scalaire(Vecteur V1, Vecteur V2);

/* Norme d'un vecteur */
double norme_vecteur(Vecteur V);

/* Distance point segment */
double distance_point_segment(Point P, Point A, Point B);

#endif