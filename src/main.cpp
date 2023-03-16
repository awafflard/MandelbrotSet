#include <iostream>
#include <SFML/Graphics.hpp>
#include "Context.hpp"
#include "mandelbrot.hpp"

int main()
{
    Context *context = new Context();

    sf::RenderWindow window(sf::VideoMode(context->getWidth(), context->getHeight()), "MandelbrotSet", sf::Style::Fullscreen);
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image pixels;

    texture.create(context->getWidth(), context->getHeight());
    pixels.create(context->getWidth(), context->getHeight(), sf::Color::White);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();

        computeImage(context, &pixels);
        texture.loadFromImage(pixels, sf::IntRect(0, 0, context->getWidth(), context->getHeight()));
        sprite.setTexture(texture);
        window.draw(sprite);
        
        window.display();
    }

    return 0;
}