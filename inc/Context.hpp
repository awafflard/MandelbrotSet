#ifndef CONTEXT_H
#define CONTEXT_H

#define IMAGE_RATIO 1.125

#include <SFML/Graphics.hpp>

class Context {

    public:
        Context();
        void init();
        void setPixel(int x, int y, int iterations, bool valid);
        sf::Color getColor(int iterations);
        bool draw();
        sf::RenderWindow *window;
        int windowWidth;
        int windowHeight;

    private:
        void initColors();
        sf::Image *pixels;
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Color colors [16];
};

#endif