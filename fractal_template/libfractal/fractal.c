#include <stdlib.h>
#include "fractal.h"

struct fractal *fractal_new(int width, int height, double a, double b)
{
    struct fractal *new = (struct fractal *) malloc(sizeof(fractal));
    if (new == NULL) exit(EXIT_FAILURE);
    new->a = a;
    new->b = b;
    new->w = width;
    new->h = height;
    new->grid = talloc(w, h);
    return new;
}

int **talloc(int w, int h) {
  int **matrice;

  matrice = (int *) malloc( w * sizeof(int*));

  if( matrice == NULL ) exit(EXIT_FAILURE);
  for( int i = 0 ; i < w ; i++ )
  {
       matrice[i] = (int *) malloc (h * sizeof(int));

       if( matrice[i] == NULL ) exit(EXIT_FAILURE);
  }

  return matrice
}

void fractal_free(struct fractal *f)
{
    /* TODO */
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    /* TODO */
    return 0;
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    /* TODO */
}

int fractal_get_width(const struct fractal *f)
{
    /* TODO */
    return 0;
}

int fractal_get_height(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_a(const struct fractal *f)
{
    /* TODO */
    return 0;
}

double fractal_get_b(const struct fractal *f)
{
    /* TODO */
    return 0;
}
