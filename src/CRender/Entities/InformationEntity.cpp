#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include "InformationEntity.h"
#include "../CRender.h"
#include "../Renderer.h"

InformationEntity::InformationEntity(CRender *cRender) : Entity(cRender) {

    if(!this->font.loadFromFile("FreeMono.ttf"))
    {
        throw std::runtime_error("Could not load font!");
    }
}

void InformationEntity::update() {

}

void InformationEntity::render() {

    sf::Text text;
    text.setFont(this->font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setStyle(sf::Text::Style::Bold);

    sf::Vector2i pixelPosition = sf::Mouse::getPosition(this->cRender->getWindow());

    // convert it to world coordinates
    sf::Vector2f mousePosition = this->cRender->getWindow().mapPixelToCoords(pixelPosition);

    text.setString("Mouse (" +
                           std::to_string((int) std::floor(mousePosition.x)) + ", " +
                           std::to_string((int) std::floor(mousePosition.y)) + ")"
    );

    this->cRender->getWindow().setView(this->cRender->getRenderer()->getOverlayView());
    this->cRender->getWindow().draw(text);
}
