#ifndef PROJECT_POINTSENTITY_H
#define PROJECT_POINTSENTITY_H

#include <vector>
#include "Entity.h"
#include "../../CCore/Point.h"

class PointsEntity : public Entity{

private:
    /**
     * A safety margin, so that we do not have blank borders around the side
     */
    int SAFETY_MARGIN = 5;

    /**
     * The maximum amount of points we are going to draw to prevent the program from freezing
     */
    int MAX_POINTS = 40000;

    std::tuple<Point, Point> range;
    std::vector<Point> primes;

public:
    PointsEntity(CRender *cRender);

    void update() override;

    void render() override;
};


#endif //PROJECT_POINTSENTITY_H
