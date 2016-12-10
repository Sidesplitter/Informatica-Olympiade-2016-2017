#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PointsEntity.h"
#include "../CRender.h"
#include "../Renderer.h"

void PointsEntity::update() {

}

void PointsEntity::render() {


    this->cRender->getWindow().setView(this->cRender->getRenderer()->getMainView());

    auto size = this->cRender->getWindow().getView().getSize();
    auto center = this->cRender->getWindow().getView().getCenter();


    //Calculate all the points that are currently visible
    auto range = std::make_tuple(
            Point((int) (center.x - size.x / 2) - SAFETY_MARGIN, (int) (center.y - size.y * -1 / 2) - SAFETY_MARGIN),
            Point(( int) (center.x + size.x / 2) + SAFETY_MARGIN, (int) (center.y + size.y * -1 / 2) + SAFETY_MARGIN)
    );

    //Set a limit for the amount of points we are going to calculate
    if((std::get<1>(range).getX() - std::get<0>(range).getX()) *
               (std::get<1>(range).getY() - std::get<0>(range).getY()) > MAX_POINTS)
    {
        return;
    }

    //If we have already calculated this range, don't do it again
    if(range != this->range)
    {
        this->range = range;
        this->primes = this->cRender->getCCore().getGaussianPrimes(this->range);
    }

    for(int i = 0; i < this->primes.size(); i++)
    {
        auto prime = this->primes[i];


        sf::RectangleShape rectangle(sf::Vector2f(1, 1));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition(sf::Vector2f(prime.getX(), prime.getY()));

        this->cRender->getWindow().draw(rectangle);
    }
}

PointsEntity::PointsEntity(CRender *cRender) : Entity(cRender) {}
