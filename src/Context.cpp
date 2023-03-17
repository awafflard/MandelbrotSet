#include "Context.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Context::Context()
{}

void Context::init()
{
    sf::VideoMode resolution = sf::VideoMode::getDesktopMode();
    this->windowWidth = (int)resolution.width;
    this->windowHeight = (int)resolution.height;

    if ((double)resolution.width / (double)resolution.height > 1.125)
    {
        this->drawZoneWidth = resolution.height * 1.125;
        this->drawZoneHeight = resolution.height;
        this->drawZoneOffsetX = (resolution.width - this->drawZoneWidth) / 2;
        this->drawZoneOffsetY = 0;
    }
    else
    {
        this->drawZoneWidth = resolution.width;
        this->drawZoneHeight = resolution.width * 1.125;
        this->drawZoneOffsetX = 0;
        this->drawZoneOffsetY = (resolution.height - this->drawZoneHeight) / 2;
    }

    this->window = new sf::RenderWindow(resolution, "Mandelbrot Set", sf::Style::Fullscreen);
    this->pixels = new sf::Image();
    this->texture = new sf::Texture();
    this->sprite = new sf::Sprite();

    this->pixels->create(this->drawZoneWidth, this->drawZoneHeight, sf::Color::White);
}

void Context::setPixel(int x, int y, bool valid)
{
    if (valid)
        this->pixels->setPixel((unsigned int)(x),(unsigned int)(y), sf::Color::Black);
    else
        this->pixels->setPixel((unsigned int)(x),(unsigned int)(y), sf::Color::White);
}

bool Context::draw()
{
        if (!this->texture->loadFromImage(*this->pixels, sf::IntRect(0, 0, this->windowWidth, this->windowHeight)))
        {
            std::cerr << "SFML: Can't create texture from image" << std::endl;
            return false;
        }
        this->sprite->setTexture(*this->texture);
        this->sprite->setPosition(this->drawZoneOffsetX, this->drawZoneOffsetY);
        this->window->draw(*this->sprite);

        return true;
}