#include <cmath>
#include "Point.h"

const Point Point::translate(const Direction direction, const int length) {

    int x = getX();
    int y= getY();

    // This could have easily be done through the use of sine and cosine.
    // But we have to take in account that the performance would be much slower.
    switch(direction)
    {
        case Direction::UP:
            y += length;
            break;
        case Direction::DOWN:
            y -= length;
            break;
        case Direction::LEFT:
            x -= length;
            break;
        case Direction::RIGHT:
            x += length;
            break;
    }

    return Point(x, y, direction);
}

Point::Point(const int x, const int y) {
    this->x = x;
    this->y = y;
}

Point::Point(const int x, const int y, Direction direction) {
    this->x = x;
    this->y = y;
    this->direction = direction;
}

const Direction Point::getDirection() const {
    return direction;
}

void Point::setDirection(Direction direction) {
    Point::direction = direction;
}

const int Point::getX() const {
    return this->x;
}

const int Point::getY() const {
    return this->y;
}

const bool Point::operator==(const Point &other) const {

    return other.getX() == getX() && other.getY() == getY();
}

const bool Point::operator!=(const Point &other) const {
    return this != &other;
}

const int Point::getDistance(const Point point) const {

    //When the points are on a horizontal/vertical line, the easiest way to calculate the distance
    //is by just doing |x1 - x2| - |y1 - y2|, this saves us some calculation time
    if(this->getX() == point.getX() || this->getY() == point.getY())
    {
        return abs(this->getX() - point.getX()) + abs(this->getY() - point.getY());
    }else{

        return std::hypot(this->getX() - point.getX(), this->getY() - point.getY());
    }

}

Point::Point() {}
