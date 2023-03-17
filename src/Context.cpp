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

    this->initColors();
}

void Context::initColors()
{
    this->colors[0] = sf::Color(66, 30, 15, 255);
    this->colors[1] = sf::Color(25, 7, 26, 255);
    this->colors[2] = sf::Color(9, 1, 47, 255);
    this->colors[3] = sf::Color(4, 4, 73, 255);
    this->colors[4] = sf::Color(0, 7, 100, 255);
    this->colors[5] = sf::Color(12, 44, 138, 255);
    this->colors[6] = sf::Color(24, 82, 177, 255);
    this->colors[7] = sf::Color(57, 125, 209, 255);
    this->colors[8] = sf::Color(134, 181, 229, 255);
    this->colors[9] = sf::Color(211, 236, 248, 255);
    this->colors[10] = sf::Color(241, 233, 191, 255);
    this->colors[11] = sf::Color(248, 201, 95, 255);
    this->colors[12] = sf::Color(255, 170, 0, 255);
    this->colors[13] = sf::Color(204, 128, 0, 255);
    this->colors[14] = sf::Color(153, 87, 0, 255);
    this->colors[15] = sf::Color(106, 52, 3, 255);
}

void Context::setPixel(int x, int y, int iterations, bool valid)
{
    if (valid)
        this->pixels->setPixel((unsigned int)(x),(unsigned int)(y), sf::Color::Black);  
    else
        this->pixels->setPixel((unsigned int)(x),(unsigned int)(y), this->getColor(iterations));
}

sf::Color Context::getColor(int iterations)
{
    return this->colors[iterations % 16];
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