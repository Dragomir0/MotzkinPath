#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WIDTH 40

#define USAGE "NAME\n\
    %s - draw a Motzkin path\n\
\n\
SYNOPSIS\n\
    %s STEPS\n\
\n\
DESCRIPTION\n\
    Draws the Motzkin path described by STEPS\n\
    The allowed steps are\n\
      r or R for a (1,0) step\n\
      u or U for a (1,1) step\n\
      d or D for a (1,-1) step\n"

enum step
{
  RIGHT,
  UP,
  DOWN
};

struct motzkin_path
{
  unsigned int width;
  unsigned int height;
  enum step steps[MAX_WIDTH];
};

/**
 * Ajouter les coordonnées de la grille dans le fichier SVG
 *
 * @param maxWidth la largeur maximale du chemin
 * @param maxHeight la hauteur maximale du chemin
 */
void printGrid(unsigned int maxWidth, unsigned int maxHeight)
{
  // Imprimer les lignes horizontales de la grille
  for (unsigned int j = 0; j <= maxHeight; j++)
  {
    fprintf(stdout, "    <line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" stroke=\"black\" stroke-width=\"1\" stroke-dasharray=\"4 2\"/>\n",
            0, j * 100, maxWidth * 100, j * 100);
  }

  // Imprimer les lignes verticales de la grille
  for (unsigned int i = 0; i <= maxWidth; i++)
  {
    fprintf(stdout, "    <line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" stroke=\"black\" stroke-width=\"1\" stroke-dasharray=\"4 2\"/>\n",
            i * 100, 0, i * 100, maxHeight * 100);
  }
}

/**
 * Ajouter les coordonnées des lignes du chemin reliant les points dans le fichier SVG
 * dependamment de la direction du chemin
 *
 * @param path le chemin à dessiner
 * @param maxHeight la hauteur maximale du chemin
 */
void printSteps(struct motzkin_path path, unsigned int maxHeight)
{
  int yValeur1 = maxHeight * 100;
  int yValeur2 = yValeur1;

  for (unsigned int i = 0; i < path.width; i++)
  {

    // Verifier la direction du chemin selon l'indice du tableau steps
    if (path.steps[i] == RIGHT)
    {
      yValeur1 = yValeur2;

      fprintf(stdout, "    <line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" stroke=\"red\" stroke-width=\"3\" stroke-dasharray=\"none\"/>\n",
              i * 100, yValeur1, (i + 1) * 100, yValeur2);
    }
    else if (path.steps[i] == UP)
    {

      yValeur2 = yValeur1 - 100;

      fprintf(stdout, "    <line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" stroke=\"red\" stroke-width=\"3\" stroke-dasharray=\"none\"/>\n",
              i * 100, yValeur1, (i + 1) * 100, yValeur2);
      yValeur1 = yValeur2;
    }
    else if (path.steps[i] == DOWN)
    {

      yValeur2 = yValeur1 + 100;

      fprintf(stdout, "    <line x1=\"%i\" y1=\"%i\" x2=\"%i\" y2=\"%i\" stroke=\"red\" stroke-width=\"3\" stroke-dasharray=\"none\"/>\n",
              i * 100, yValeur1, (i + 1) * 100, yValeur2);
      yValeur1 = yValeur2;
    }
  }
}

/**
 * Ajouter les coordonnées des points du chemin dans le fichier SVG dependamment de la direction du chemin
 *
 * @param path  le chemin à dessiner
 * @param maxHeight la hauteur maximale du chemin
 */
void printPoints(struct motzkin_path path, unsigned int maxHeight)
{
  int xValeur = 0;
  int yValeur = maxHeight * 100;

  for (unsigned int i = 0; i <= path.width; i++)
  {
    fprintf(stdout, "    <circle cx=\"%i\" cy=\"%i\" r=\"7\" fill=\"blue\"/>\n", xValeur, yValeur);

    // Changer les coordonnées du point selon la direction du chemin
    if (i < path.width)
    {
      if (path.steps[i] == RIGHT)
      {
        xValeur += 100;
      }
      else if (path.steps[i] == UP)
      {
        xValeur += 100;
        yValeur -= 100;
      }
      else if (path.steps[i] == DOWN)
      {
        xValeur += 100;
        yValeur += 100;
      }
    }
  }
}

/**
 * Initialiser les valeurs de la structure path selon l'argument fourni en ligne de commande
 *
 * @param path le chemin à dessiner
 * @param argumentNbreLettres l'argument fourni en ligne de commande
 * @param maxWidth la largeur maximale du chemin
 * @param maxHeight la hauteur maximale du chemin
 * @param currentHeight la hauteur du chemin signée pour savoir si chemin descend en dessous axe horizontal
 * @return int la valeur de retour
 */
int initializerValeursChemin(struct motzkin_path *path, char *argumentNbreLettres, unsigned int *maxWidth, unsigned int *maxHeight, int *currentHeight)
{
  bool returnVal = false;

  for (int i = 0; argumentNbreLettres[i] != '\0'; i++)
  {
    char c = argumentNbreLettres[i];

    if (c == 'r')
    {
      path->width++;
      (*maxWidth)++;
      path->steps[i] = RIGHT;
    }
    else if (c == 'u')
    {
      path->height++;
      (*currentHeight)++;
      (*maxHeight)++;
      path->width++;
      (*maxWidth)++;
      path->steps[i] = UP;
    }
    else if (c == 'd')
    {
      path->height--;
      (*currentHeight)--;
      path->width++;
      (*maxWidth)++;
      path->steps[i] = DOWN;
    }
    else
    {
      fprintf(stderr, "error: invalid character '%c' in path at position %d\n", c, i);
      returnVal = true;
    }
  }
  return returnVal;
}

/**
 * Créer le fichier SVG en appelant les fonctions printGrid, printSteps et printPoints
 * et en rajoutant la base de code du fichier SVG
 *
 * @param path  le chemin à dessiner
 * @param maxWidth la largeur maximale du chemin
 * @param maxHeight la hauteur maximale du chemin
 * @return int la valeur de retour
 */
int ecrireFichierSVG(struct motzkin_path path, unsigned int maxWidth, unsigned int maxHeight)
{

  fprintf(stdout, "<?xml version=\"1.0\"?>\n");
  fprintf(stdout, "<svg width=\"%i\" height=\"%i\" viewBox=\"-8 -8 %i %i\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n",
          maxWidth * 100, maxHeight * 100, maxWidth * 100, (maxHeight + 1) * 100);
  fprintf(stdout, "  <g id=\"grid\">\n");

  printGrid(maxWidth, maxHeight);

  fprintf(stdout, "  </g>\n");
  fprintf(stdout, "  <g id=\"steps\">\n");

  printSteps(path, maxHeight);

  fprintf(stdout, "  </g>\n");
  fprintf(stdout, "<g id=\"points\">\n");

  printPoints(path, maxHeight);

  fprintf(stdout, "  </g>\n");
  fprintf(stdout, "</svg>\n");

  return 0;
}

/**
 * Cette methode lit l'argument fourni en ligne de commande et affiche le chemin Motzkin
 * correspondant en fichier SVG
 *
 * @param argc le nombre d'arguments du programme
 * @param argv les arguments du programme
 * @return int la valeur de retour
 */
int main(int argc, char *argv[])
{

  if (argc < 2)
  {
    fprintf(stderr, "error: wrong number of arguments\n");
    fprintf(stderr, USAGE, argv[0], argv[0]);
    return 1;
  }

  char *argumentNbreLettres = argv[1];

  int longeurChemin = strlen(argumentNbreLettres);
  unsigned int maxHeight = 0, maxWidth = 0;

  if (longeurChemin > 40)
  {
    fprintf(stderr, "error: the path cannot be wider than 40\n");
    fprintf(stderr, USAGE, argv[0], argv[0]);
    return 1;
  }

  struct motzkin_path path;
  int currentHeight = 0;

  int validiteValeursChemin = initializerValeursChemin(&path, argumentNbreLettres, &maxWidth, &maxHeight, &currentHeight);
  if (validiteValeursChemin == 1)
  {
    return 1;
  }

  if (currentHeight < 0)
  {
    fprintf(stderr, "error: the path cannot go below the horizontal axis\n");
    fprintf(stderr, USAGE, argv[0], argv[0]);
    return 1;
  }

  if (currentHeight != 0)
  {
    fprintf(stderr, "error: the path cannot end above the horizontal axis\n");
    fprintf(stderr, "Final path height: %d\n", currentHeight);
    fprintf(stderr, USAGE, argv[0], argv[0]);
    return 1;
  }

  return (ecrireFichierSVG(path, maxWidth, maxHeight));
}