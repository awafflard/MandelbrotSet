#ifndef MANDELBROT_H
#define MANDELBROT_H

#define X1 -2.1
#define X2 0.6
#define Y1 -1.2
#define Y2 1.2
#define MAX_ITERATIONS 50

#include "Context.hpp"
#include <SFML/Graphics.hpp>

void computeImage(Context *context);
int mandelbrot(double x, double y);

#endif