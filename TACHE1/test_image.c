#include "image.h"
#include "types_macros.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
        srand(time(NULL));

        if (argc < 2)
        {
          printf("[USAGE] : ./test_image image.pbm image_sortie.pbm\n");
          return -1;
        }
        
        Image A;

        A = lire_fichier_image(argv[1]);
        printf("** Image : **\n");
        ecrire_image(A);
       
        /* Ici on test la fonction set_pixel_image() avec des entiers générés
        ** de façon pseudo-aléatoire  */
        if (A.L > 0 && A.H > 0)
        {
          for (int i = 0 ; i < 20 ; i++)
          {
            set_pixel_image(A, rand() % A.L, rand() % A.H, NOIR);
          }
        
        
        printf("** Image après modification : **\n");
        ecrire_image(A);    
        sauvegarder_image(A,argv[2]);  // On sauvegarde l'image après modification
        
        printf("Nouvelle image enregistrée sous le nom %s\n", argv[2]);
        }

        }
