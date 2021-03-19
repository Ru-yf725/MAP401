#include "image.h"
#include "types_macros.h"
#include <stdlib.h>
#include <time.h>
/*
int main(int argc, char** argv)
{
        srand(time(NULL));

        if (argc < 2)
        {
          printf("[USAGE] : ./test_image image.pbm\n");
          return -1;
        }
        
        Image A;

        A = lire_fichier_image(argv[1]);
        printf("** Image : **\n");
        ecrire_image(A);
        
        for (int i = 0 ; i < 20 ; i++)
        {
          set_pixel_image(A, rand() % A.L, rand() % A.H, NOIR);
        }

        printf("** Image après modification : **\n");
        ecrire_image(A);    
        sauvegarder_image(A,"output.pbm");
        printf("Nouvelle image enregistrée sous le nom output.pbm\n");
}
*/
int main(int argc, char** argv)
{
    Image A;

    A = lire_fichier_image(argv[1]);
  
    agrandissement_double(A);

    ecrire_image(A);
}
