#ifndef PROJECT_INFORMATIONENTITY_H
#define PROJECT_INFORMATIONENTITY_H

#include <SFML/Graphics/Font.hpp>
#include "Entity.h"

class InformationEntity : public Entity{
private:
    sf::Font font;

public:
    InformationEntity(CRender *cRender);

    void render() override;

    void update() override;

};


#endif //PROJECT_INFORMATIONENTITY_H
