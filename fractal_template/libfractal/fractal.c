#include <stdlib.h>
#include "fractal.h"

int **talloc(int w, int h) {
  int **matrix;

  matrix = (int **) malloc( w * sizeof(int *));
  if( matrix == NULL ) exit(EXIT_FAILURE);

  for( int i = 0 ; i < w ; i++ )
  {
       matrix[i] = (int *) malloc (h * sizeof(int));
       if( matrix[i] == NULL ) exit(EXIT_FAILURE);
  }

  return matrix;
}

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
    struct fractal *new = (struct fractal *) malloc(sizeof(fractal));
    if (new == NULL) exit(EXIT_FAILURE);
    new->a = a;
    new->b = b;
    new->w = width;
    new->h = height;
    new->grid = talloc(w, h);
    new->name = name;
    return new;
}

void fractal_free(struct fractal *f)
{
    int **matrix = f->grid;
    for (int i = 0; i < new->w; i ++) free(matrix[i]);
    free(name);
    free(f);
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
    return f->grid[x][y];
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
    f->grid[x][y] = val;
}

int fractal_get_width(const struct fractal *f)
{
    return f->w;
}

int fractal_get_height(const struct fractal *f)
{
    return f->h;
}

double fractal_get_a(const struct fractal *f)
{
    return f->a;
}

double fractal_get_b(const struct fractal *f)
{
    return f->b;
}

const char *fractal_get_name(const struct fractal *f) {
  return f->name;
}
