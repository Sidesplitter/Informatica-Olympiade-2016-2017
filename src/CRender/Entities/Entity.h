#ifndef PROJECT_ENTITY_H
#define PROJECT_ENTITY_H

class CRender;

class Entity {

protected:
    CRender * cRender;
public:
    Entity(CRender *cRender) {
        this->cRender = cRender;
    };

    virtual void update() = 0;
    virtual void render() = 0;

};


#endif //PROJECT_ENTITY_H
