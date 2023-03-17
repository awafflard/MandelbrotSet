#ifndef CONTEXT_H
#define CONTEXT_H

#define IMAGE_RATIO 1.125

#include <SFML/Graphics.hpp>

class Context {

    public:
        Context();
        void init();
        void setPixel(int x, int y, bool valid);
        bool draw();
        sf::RenderWindow *window;
        int windowWidth;
        int windowHeight;
        int drawZoneWidth;
        int drawZoneHeight;
        int drawZoneOffsetX;
        int drawZoneOffsetY;

    private:
        sf::Image *pixels;
        sf::Texture *texture;
        sf::Sprite *sprite;

};

#endif