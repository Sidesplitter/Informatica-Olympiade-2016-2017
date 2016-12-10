#include <stdexcept>
#include "CRender.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "Entities/PointsEntity.h"
#include "Entities/PathEntity.h"
#include "Entities/InformationEntity.h"

Renderer * CRender::getRenderer() const {
    return renderer;
}

CRender::CRender() : renderer(renderer) {

    this->window.create(sf::VideoMode(800, 600), "CRender");
    this->window.setVerticalSyncEnabled(true);

    this->renderer = new Renderer(this);
    this->inputHandler = new InputHandler(this);

    this->renderer->getEntities().push_back(new PointsEntity(this));

    this->renderer->getEntities().push_back(new InformationEntity(this));
    //TODO don't hardcode this
    auto path = Path(Point(174, 89), this->getCCore().getPrimalityTester());
    path.calculatePath(std::make_tuple(Point(0, 0), Point(1000, 1000)));
    this->renderer->getEntities().push_back(new PathEntity(this, path));
}

sf::RenderWindow & CRender::getWindow() {
    return window;
}

const void CRender::run() {

    while (this->window.isOpen()) {

        sf::Event event;
        while (this->window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                this->window.close();
            }

            if (event.type == sf::Event::Resized) {

                int height = event.size.height;

                this->getRenderer()->getOverlayView().setSize(sf::Vector2f(event.size.width, event.size.height));
                this->getRenderer()->getOverlayView().setCenter(event.size.width / 2, event.size.height / 2);

                this->getRenderer()->getMainView().setSize(sf::Vector2f(event.size.width, -height));
                this->getRenderer()->getMainView().zoom(0.125);
            }

            this->getInputHandler()->handleEvent(event);
        }

        this->getInputHandler()->update();
        this->getRenderer()->render();

    }
}

InputHandler *CRender::getInputHandler() const {
    return inputHandler;
}

CCore &CRender::getCCore() {
    return cCore;
}
