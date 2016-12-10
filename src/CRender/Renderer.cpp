#include "Renderer.h"
#include "CRender.h"
#include "Entities/Entity.h"

std::vector<Entity*> & Renderer::getEntities() {
    return this->entities;
}

Renderer::Renderer(CRender *cRender) : cRender(cRender) {

    this->cRender = cRender;
    this->mainView.setCenter(sf::Vector2f(0, 0));
    this->mainView.setSize(sf::Vector2f(800, -600));

    this->overlayView.setCenter(sf::Vector2f(0 ,0));
    this->overlayView.setSize(sf::Vector2f(800, 600));
}

sf::View &Renderer::getOverlayView() {
    return overlayView;
}

const void Renderer::render() const {


    this->getCRender()->getWindow().clear(sf::Color::White);

    //Draw all the objects
    for (int i = 0; i < entities.size(); i++) {

        entities[i]->render();
    }

    this->getCRender()->getWindow().display();
}

CRender * Renderer::getCRender() const {
    return cRender;
}

sf::View &Renderer::getMainView() {
    return mainView;
}
