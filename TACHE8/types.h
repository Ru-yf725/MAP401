typedef struct Vecteur_
{ 
  double x,y; // coordonnées
} Vecteur;

typedef struct Point_
{
  double x,y; // coordonnées
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
/*
typedef struct Liste_Bezier_
{
	int taille;
	Bezier3* tab;
} Liste_Bezier;*/