#include <iostream>
#include <SFML/Graphics.hpp>
#include "Context.hpp"
#include "mandelbrot.hpp"
#include "FpsCounter.hpp"

int main()
{
    Context *context = new Context();

    context->init();

    FpsCounter counter;
    
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

        context->window->clear(sf::Color::Black);

        computeImage(context);
        if(!context->draw())
        {
            context->window->close();
            delete(context);
            return -1;
        }
        else
        {
            counter.draw(context->window);
            context->window->display();
        }

    }

    delete(context);

    return 0;
}