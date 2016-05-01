#include <stdlib.h>
#include "fractal.h"


int *talloc(int w, int h) {
  int *matrix;

  matrix = (int *) malloc( h*w * sizeof(int));
  if( matrix == NULL ) exit(EXIT_FAILURE);

  return matrix;
}

struct fractal *fractal_new(const char *name, int width, int height, double a, double b)
{
    struct fractal *new = (struct fractal *) malloc(sizeof(struct fractal));
    if (new == NULL) exit(EXIT_FAILURE);
    new->a = a;
    new->b = b;
    new->w = width;
    new->h = height;
    new->grid = talloc(width, height);
    new->name = name;
    return new;
}


void fractal_free(struct fractal *f)
{
  //free(f->grid);
  //free(f->name);
  //free(f);
}

int fractal_get_value(const struct fractal *f, int x, int y)
{
  int h = fractal_get_height(f);
  return f->grid[x * h + y];
}

void fractal_set_value(struct fractal *f, int x, int y, int val)
{
  int h = fractal_get_height(f);
  f->grid[x * h + y] = val;
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
