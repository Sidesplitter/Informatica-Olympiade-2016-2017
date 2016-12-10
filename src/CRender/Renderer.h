#include <vector>
#include <SFML/Graphics/View.hpp>

#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

class Entity;
class CRender;

class Renderer {

private:
    CRender * cRender;
    sf::View mainView;
    sf::View overlayView;

    std::vector<Entity*> entities;


public:
    std::vector<Entity*> &getEntities();

    CRender *getCRender() const;


    const void render() const;
    Renderer(CRender *cRender);

    sf::View &getMainView();

    sf::View &getOverlayView();
};


#endif //PROJECT_RENDERER_H
