#include "geom2d.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
  Point A, B, C;
  Vecteur U;
  Vecteur V = {5.2,4.1};

  A = set_point(1.0, -3.0);
  B = set_point(4.0, 1.0);
  C = add_point(A,B);
  U = vect_bipoint(C,A);
  printf("A = ");
  afficher_point(A);
  printf("B = ");
  afficher_point(B);
  printf("C = ");
  afficher_point(C);
  printf("U = ");
  afficher_vecteur(U);
  printf("La distance entre les points A et B : %f\n ",distance(A,B));
  printf("La soustraction des deux vecteurs U et V est : \n");
  afficher_vecteur(soustraction(U,V));
  printf("Le vecteur V multiplié par le scalaire 3 est : \n");
  afficher_vecteur(mult_scalaire(3,V));
  printf("La norme du vecteur U est :%f\n", norme_vecteur(U));
}
