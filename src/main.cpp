#include <iostream>
#include <SFML/Graphics.hpp>
#include "Context.hpp"
#include "mandelbrot.hpp"

int main()
{
    Context *context = new Context();

    context->init();
    
    while (context->window->isOpen())
    {
        sf::Event event;
        while (context->window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    context->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        context->window->close();
                    break;
                default:
                    break;
            }
        }

        context->window->clear(sf::Color::White);

        computeImage(context);
        if(!context->draw())
        {
            context->window->close();
            delete(context);
            return -1;
        }
        else
            context->window->display();
    }

    delete(context);

    return 0;
}