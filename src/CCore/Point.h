#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_POINT_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_POINT_H

#include <tuple>
#include "Directions.h"

class Point {
private:
    int x;
    int y;
    Direction direction;

public:
    Point(const int x, const int y);

    Point(const int x, const int y, Direction direction);

    Point();

    /**
     * Create a new point that is translated relative to this point.
     *
     * @param direction
     * @param length
     * @return
     */
    const Point translate(const Direction direction, const int length = 1);

    const int getX() const;

    const int getY() const;

    const bool operator==(const Point &other) const;

    const bool operator!=(const Point &other) const;

    const Direction getDirection() const;

    void setDirection(Direction direction);

    const int getDistance(const Point point) const;

};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_POINT_H
