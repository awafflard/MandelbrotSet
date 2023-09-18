#include "FpsCounter.hpp"
#include <sstream>
#include "NunitoMediumItalic.hpp"

FpsCounter::FpsCounter()
{
    this->background.setSize(sf::Vector2f(150.f, 40.f));
    this->background.setPosition(0, 0);
    this->background.setFillColor(sf::Color::Black);
    this->font.loadFromMemory(&Nunito_MediumItalic_ttf, Nunito_MediumItalic_ttf_len);
    this->calculationTime.setFont(this->font);
    this->calculationTime.setCharacterSize(12);
    this->calculationTime.setPosition(5, 5);
    this->calculationTime.setFillColor(sf::Color::White);
    this->calculationTime.setOutlineColor(sf::Color::White);
    this->framesPerSecond.setFont(this->font);
    this->framesPerSecond.setCharacterSize(12);
    this->framesPerSecond.setPosition(5, 22);
    this->framesPerSecond.setFillColor(sf::Color::White);
    this->framesPerSecond.setOutlineColor(sf::Color::White);
}

void FpsCounter::draw(sf::RenderWindow *window)
{
    std::stringstream calcTime;
    std::stringstream fps;

    this->elapsed = this->clock.restart();
    calcTime << "Processing time: " << elapsed.asMilliseconds() << "ms";
    this->calculationTime.setString (calcTime.str());
    fps << "FPS: " << 1000 / elapsed.asMilliseconds();
    this->framesPerSecond.setString(fps.str());
    window->draw(this->background);
    window->draw(this->calculationTime);
    window->draw(this->framesPerSecond);
}