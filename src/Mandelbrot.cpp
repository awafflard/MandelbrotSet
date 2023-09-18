#include "Mandelbrot.hpp"
#include "ComplexNumber.hpp"
#include "Context.hpp"
#include <SFML/Graphics.hpp>

Mandelbrot::Mandelbrot()
{
    this->xMin = -2.1;
    this->xMax = 0.6;
    this->yMin = -1.2;
    this->yMax = 1.2;
    this->xStart = this->xMin;
    this->xEnd = this->xMax;
    this->yStart = this->yMin;
    this->yEnd = this->yMax;
    this->zoomFactor = 1.1;
    this->iterations = 256;
}

Mandelbrot* Mandelbrot::getInstance()
{
    if (Mandelbrot::instance == nullptr)
        Mandelbrot::instance = new Mandelbrot();
    return Mandelbrot::instance;
}

void Mandelbrot::setZoom(Context* context, int posX, int posY, int delta)
{
    double fractalX = this->xStart + ((double)posX / context->windowWidth) * (this->xEnd- this->xStart);
    double fractalY = this->yStart + ((double)posY / context->windowHeight) * (this->yEnd - this->yStart);

    double newXMin = 0.0;
    double newXMax = 0.0;
    double newYMin = 0.0;
    double newYMax = 0.0;
    
    if (delta > 0)
    {
        newXMin = fractalX - (fractalX - this->xStart) / this->zoomFactor;
        newXMax = fractalX + (this->xEnd - fractalX) / this->zoomFactor;
        newYMin = fractalY - (fractalY - this->yStart) / this->zoomFactor;
        newYMax = fractalY + (this->yEnd - fractalY) / this->zoomFactor;
    }
    else
    {
        newXMin = fractalX - (fractalX - this->xStart) * this->zoomFactor;
        newXMax = fractalX + (this->xEnd - fractalX) * this->zoomFactor;
        newYMin = fractalY - (fractalY - this->yStart) * this->zoomFactor;
        newYMax = fractalY + (this->yEnd - fractalY) * this->zoomFactor;
    }

    if (newXMin < this->xMin)
    {
        double diff = this->xMin - newXMin;
        newXMin += diff;
        newXMax += diff;
    }

    if (newXMax > this->xMax)
    {
        double diff = newXMax - this->xMax;
        newXMin -= diff;
        newXMax -= diff;
    }
    
    if (newYMin < this->yMin)
    {
        double diff = this->yMin - newYMin;
        newYMin += diff;
        newYMax += diff;
    }
    
    if (newYMax > this->yMax)
    {
        double diff = newYMax - this->yMax;
        newYMin -= diff;
        newYMax -= diff;
    }

    if (newXMax - newXMin > this->xMax - this->xMin || newYMax - newYMin > this->yMax - this->yMin)
        Mandelbrot::resetView();
    else
    {
        this->xStart = newXMin;
        this->xEnd = newXMax;
        this->yStart = newYMin;
        this->yEnd = newYMax;
    }
}

void Mandelbrot::resetView()
{
    fprintf(stderr, "View reset command received\n");
    this->xStart = this->xMin;
    this->xEnd = this->xMax;
    this->yStart = this->yMin;
    this->yEnd = this->yMax;
}


void Mandelbrot::computeImage(Context *context)
{
    double stepX = context->windowWidth / (this->xEnd - this->xStart);
    double stepY = context->windowHeight / (this->yEnd - this->yStart);
    double relativeX = 0.0;
    double relativeY = 0.0;
    int it = 0;

    for (int x = 0; x < context->windowWidth; x++)
    {
        for (int y = 0; y < context->windowHeight; y++)
        {
            relativeX = x / stepX + this->xStart;
            relativeY = y / stepY + this->yStart;
            it = this->mandelbrot(relativeX, relativeY);
            context->setPixel(x, y, it, it == this->iterations ? true : false);
        }
    }
}

int Mandelbrot::mandelbrot(double x, double y)
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
    } while (z.r * z.r + z.i * z.i < 4.0 && i < this->iterations);

    return i;
}
