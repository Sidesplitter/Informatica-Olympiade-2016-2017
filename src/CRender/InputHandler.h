#ifndef PROJECT_INPUTHANDLER_H
#define PROJECT_INPUTHANDLER_H

#include <SFML/Window/Event.hpp>

class CRender;

class InputHandler {

private:
    CRender * cRender;
    int movementSpeed = 2;
    float zoom = 1;
    sf::Vector2i previousMousePosition;

public:
    InputHandler(CRender *cRender);
    CRender *getCRender() const;
    void update();
    void handleEvent(sf::Event event);
};


#endif //PROJECT_INPUTHANDLER_H
