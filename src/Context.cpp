#include "Context.hpp"
#include <SFML/Graphics.hpp>

Context::Context()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    width = mode.width;
    height = mode.height;
}

int Context::getHeight()
{
    return height;
}

int Context::getWidth()
{
    return width;
}