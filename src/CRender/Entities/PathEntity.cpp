#include <SFML/Graphics.hpp>
#include <math.h>
#include "PathEntity.h"
#include "../CRender.h"
#include "../Renderer.h"

const Path &PathEntity::getPath() const {
    return path;
}

void PathEntity::setPath(const Path &path) {
    PathEntity::path = path;
}

PathEntity::PathEntity(CRender *cRender, const Path &path) : Entity(cRender), path(path) {}

void PathEntity::update() {

    }

void PathEntity::render() {

    this->cRender->getWindow().setView(this->cRender->getRenderer()->getMainView());

    sf::VertexArray lines(sf::PrimitiveType::LinesStrip, this->getPath().getPoints().size());

    for(int i = 0; i < this->getPath().getPoints().size(); i++){

        auto point = this->getPath().getPoints()[i];

        lines[i].color = sf::Color::Red;
        //Add 0,5 to center it
        lines[i].position = sf::Vector2f(point.getX() + 0.5f, point.getY() + 0.5f);

        if(i == 0)
        {
            sf::CircleShape originCircle(0.5);
            originCircle.setFillColor(sf::Color::Green);
            originCircle.setPosition(point.getX(), point.getY());
            this->cRender->getWindow().draw(originCircle);
        }

        if(i > 0) {
            float radius = 0.5f;
            auto prevPoint = this->getPath().getPoints()[i - 1];

            float x = (point.getX() + prevPoint.getX()) / 2;
            float y = (point.getY() + prevPoint.getY()) / 2;


            sf::CircleShape directionTriangle(radius, 3);
            directionTriangle.setFillColor(sf::Color::Red);
            directionTriangle.setPosition(sf::Vector2f(x, y));

            sf::Transform transform;

            int angle = std::atan2(point.getX() - prevPoint.getX(), point.getY() - prevPoint.getY()) * 180 / M_PI;
            transform.rotate(angle, x + radius, y + radius);

            this->cRender->getWindow().draw(directionTriangle, transform);
        }
    }

    this->cRender->getWindow().draw(lines);
}
