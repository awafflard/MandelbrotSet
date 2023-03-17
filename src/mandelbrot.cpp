#include "mandelbrot.hpp"
#include "ComplexNumber.hpp"
#include "Context.hpp"
#include <SFML/Graphics.hpp>

void computeImage(Context *context)
{
    double zoomX = context->drawZoneWidth / (X2 - X1);
    double zoomY = context->drawZoneHeight / (Y2 - Y1);
    double relativeX(0.0);
    double relativeY(0.0);
    int iterations(0);

    for (int x = 0; x < context->drawZoneWidth; x++)
    {
        for (int y = 0; y < context->drawZoneHeight; y++)
        {
            relativeX = x / zoomX + X1;
            relativeY = y / zoomY + Y1;
            iterations = mandelbrot(relativeX, relativeY);
            context->setPixel(x, y, iterations, iterations == MAX_ITERATIONS ? true : false);
        }
    }
}

int mandelbrot(double x, double y)
{
    ComplexNumber c = ComplexNumber(x, y);
    ComplexNumber z = ComplexNumber();
    int i(0);

    do
    {
        double tmp = z.r;
        z.r = z.r * z.r - z.i * z.i + c.r;
        z.i = 2 * z.i * tmp + c.i;
        i++;
    } while (z.r * z.r + z.i * z.i < 4.0 && i < MAX_ITERATIONS);

    return i;
}