typedef struct Vecteur_
{ 
  double x,y; // Coordonnées d'un vecteur
} Vecteur;

typedef struct Point_
{
  double x,y; // Coordonnées d'un point
} Point;

typedef struct Bezier2_
{
  Point C0;
  Point C1;
  Point C2;
} Bezier2;

typedef struct Bezier3_
{
  Point C0;
  Point C1;
  Point C2;
  Point C3;
} Bezier3;