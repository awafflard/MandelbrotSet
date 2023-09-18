#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Context.hpp"

class Mandelbrot {

    public:
        Mandelbrot& operator= (const Mandelbrot&) = delete;
        Mandelbrot(const Mandelbrot&) = delete;
        static Mandelbrot* getInstance();
        void setZoom(Context* context, int posX, int posY, int delta);
        void resetView();
        void computeImage(Context* context);

    private:
        inline static Mandelbrot* instance{nullptr};
        Mandelbrot();
        ~Mandelbrot() = default;
        int mandelbrot(double x, double y);
        double xMin;
        double xMax;
        double yMin;
        double yMax;
        double xStart;
        double xEnd;
        double yStart;
        double yEnd;
        double zoomFactor;
        int iterations;
};

#endif