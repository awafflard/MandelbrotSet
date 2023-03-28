#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SFML/Graphics.hpp>

class FpsCounter {
    public:
        FpsCounter();
        void draw(sf::RenderWindow *window);
        
    private:
        sf::RectangleShape background;
        sf::Clock clock;
        sf::Time elapsed;
        sf::Font font;
        sf::Text calculationTime;
        sf::Text framesPerSecond;        
};

#endif
