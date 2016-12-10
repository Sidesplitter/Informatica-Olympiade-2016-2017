#include <SFML/Graphics/RenderWindow.hpp>
#include "../CCore/CCore.h"

#ifndef PROJECT_CRENDER_H
#define PROJECT_CRENDER_H

class InputHandler;
class Renderer;

class CRender {

private:
    CCore cCore;
    InputHandler * inputHandler;
    Renderer *renderer;
    sf::RenderWindow window;
    bool focus = false;

public:

    CRender();
    Renderer * getRenderer() const;

    const void run();

    CCore &getCCore();
    sf::RenderWindow &getWindow();

    InputHandler *getInputHandler() const;
};


#endif //PROJECT_CRENDER_H
