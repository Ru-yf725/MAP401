typedef struct Vecteur_
{ 
  double x,y; // coordonnées
} Vecteur;

typedef struct Point_
{
  double x,y; // coordonnées
} Point;

// Type bezier de degré 2
typedef struct Bezier2_
{
  Point C0;
  Point C1;
  Point C2;
} Bezier2;

// Type bezier de degré 3
typedef struct Bezier3_
{
  Point C0;
  Point C1;
  Point C2;
  Point C3;
} Bezier3;