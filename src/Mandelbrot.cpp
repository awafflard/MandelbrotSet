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
    this->currentZoomLevel = 1.0;
    this->minIterations = 32;
    this->iterations = 32;
    this->framesAtCurentIterations = 0;
    this->maxFramesAtCurentIterations = 2;
    this->maxIterations = 1024;
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

    this->currentZoomLevel = 1.0 / ((this->xEnd - this->xStart) / (this->xMax - this->xMin));
    this->framesAtCurentIterations = 0;

    if (this->currentZoomLevel < 3.0)
        this->iterations = this->minIterations < 32 ? 32 : this->minIterations;
    else if (3.0 <= this->currentZoomLevel  && this->currentZoomLevel < 5.0)
        this->iterations = this->minIterations < 32 ? 32 : this->minIterations;
    else if (5.0 <= this->currentZoomLevel && this->currentZoomLevel < 1.0e2)
        this->iterations = this->minIterations < 64 ? 64 : this->minIterations;
    else if (1.0e2 <= this->currentZoomLevel && this->currentZoomLevel < 1.0e3)
        this->iterations = this->minIterations < 128 ? 128 : this->minIterations;
    else if (1.0e3 <= this->currentZoomLevel && this->currentZoomLevel < 1.0e4)
        this->iterations = this->minIterations < 256 ? 256 : this->minIterations;
    else if (1.0e4 <= this->currentZoomLevel && this->currentZoomLevel < 1.0e7)
        this->iterations = this->minIterations < 512 ? 512 : this->minIterations;
    else
        this->iterations = this->minIterations < 1024 ? 1024 : this->minIterations;

    if (this->maxIterations < this->iterations)
        this->maxIterations = this->iterations;

}

void Mandelbrot::resetView()
{
    this->xStart = this->xMin;
    this->xEnd = this->xMax;
    this->yStart = this->yMin;
    this->yEnd = this->yMax;
    this->currentZoomLevel = 1.0;
}


void Mandelbrot::computeImage(Context *context)
{
    double stepX = context->windowWidth / (this->xEnd - this->xStart);
    double stepY = context->windowHeight / (this->yEnd - this->yStart);
    double relativeX = 0.0;
    double relativeY = 0.0;
    int it = 0;

    if (this->framesAtCurentIterations >= this->maxFramesAtCurentIterations)
    {
        if (this->iterations < this->maxIterations)
            this->iterations *= 2;
        this->framesAtCurentIterations = 0;
    }

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
    this->framesAtCurentIterations++;
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
