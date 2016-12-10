#include <iostream>
#include "InputHandler.h"
#include "CRender.h"
#include "Renderer.h"

InputHandler::InputHandler(CRender *cRender) : cRender(cRender) {}

CRender *InputHandler::getCRender() const {
    return cRender;
}

void InputHandler::update() {

    //If the window does not have focus, do not update anything.
    if(!this->getCRender()->getWindow().hasFocus())
    {
        return;
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(this->cRender->getWindow());
    //Dragging
    if(this->previousMousePosition != mousePosition && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        //Convert it to relative coordinates to make sure dragging is at an equal speed for every zoom level
        sf::Vector2f relativePrevPosition = this->cRender->getWindow().mapPixelToCoords(previousMousePosition);
            sf::Vector2f relativeMousePosition = this->cRender->getWindow().mapPixelToCoords(mousePosition);


        this->getCRender()->getRenderer()->getMainView().move(
                relativePrevPosition.x - relativeMousePosition.x,
                relativePrevPosition.y - relativeMousePosition.y
        );
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->getCRender()->getRenderer()->getMainView().move(0, this->movementSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->getCRender()->getRenderer()->getMainView().move(0, -this->movementSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->getCRender()->getRenderer()->getMainView().move(-this->movementSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->getCRender()->getRenderer()->getMainView().move(this->movementSpeed, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        {
            this->zoom = 0.95;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        {
            this->zoom = 1.05;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        {
            this->getCRender()->getRenderer()->getMainView().setCenter(0, 0);
        }
    }

    this->cRender->getWindow().setView(this->cRender->getRenderer()->getMainView());


    this->getCRender()->getRenderer()->getMainView().zoom(this->zoom);

    //Reset values
    this->zoom = 1;
    this->previousMousePosition = mousePosition;
}

void InputHandler::handleEvent(sf::Event event) {

    if (event.type == sf::Event::MouseWheelMoved)
    {
        this->zoom = 1.3;

        if(event.mouseWheel.delta == 1)
        {
            this->zoom = 0.7;
        }
    }

}
