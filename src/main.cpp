#include <iostream>
#include <SFML/Graphics.hpp>
#include "Context.hpp"
#include "Mandelbrot.hpp"
#include "FpsCounter.hpp"

void handleMouseWheelEvent(sf::Event& event, Context* context, Mandelbrot* mandelbrot)
{
    mandelbrot->setZoom(context, event.mouseWheel.x, event.mouseWheel.y, event.mouseWheel.delta);
}

int main()
{
    Context* context = new Context();
    Mandelbrot* mandelbrot = Mandelbrot::getInstance();

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
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                        mandelbrot->resetView();
                    break;
                case sf::Event::MouseWheelMoved:
                    handleMouseWheelEvent(event, context, mandelbrot);
                    break;
                default:
                    break;
            }
        }

        context->window->clear(sf::Color::Black);

        mandelbrot->computeImage(context);
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