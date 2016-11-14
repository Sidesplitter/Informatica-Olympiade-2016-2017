#include <vector>
#include "Path.h"

void Path::calculatePath(std::tuple<Point, Point> searchArea, bool squareOptimization,
                         int minimalLength, int maximumPoints) {

    // The starting point is not a gaussian prime, we can stop already
    if(!this->primalityTester->isGaussianPrime(this->startingPoint))
    {
        return;
    }

    // A list with all the found Gaussian points in this loop
    std::vector<Point> points = {};

    // The length of a side (Only used when squareOptimization is true)
    int sideLength = 0;

    // The total length of the loop
    int length = 0;

    // The current point we are staying on
    // This is not necessary a gaussian point.
    Point point = this->startingPoint;
    point.setDirection(Direction::DOWN);

    //Continue till we have found the maximum amount of points
    while (maximumPoints == 0 || points.size() < maximumPoints) {

        //We are outside the X range
        if (point.getX() < std::get<0>(searchArea).getX() || point.getX() > std::get<1>(searchArea).getX()) {
            break;
        }

        //We are outside the Y range
        if (point.getY() < std::get<0>(searchArea).getY() || point.getY() > std::get<1>(searchArea).getY()) {
            break;
        }

        if (this->primalityTester->isGaussianPrime(point)) {

            // Add the point to the list of points
            points.push_back(point);

            // We found a loop: The coordinates are equal and we are currently going down,
            // which means that we will turn right soon (and thus go into a loop)
            if (points.size() > 1 && point == this->startingPoint && point.getDirection() == Direction::DOWN) {
                this->loop = true;

                // The loop is a square when it has five points (The first and the last point are added separately)
                // and when the first two points have the same length as the second and the third point
                if (points.size() == 5) {
                    this->square = points[0].getDistance(points[1]) == points[1].getDistance(points[2]);

                    if(this->square)
                    {
                        this->sideLength = this->getLength() / 4;
                    }
                }

                break;
            }

            //These optimizations can only take place if we are looking for a square
            if (squareOptimization) {
                // We no exactly one side, if this side is smaller than the minimal length we can stop.
                // We can also determine the length of a a side
                if (points.size() == 2) {
                    sideLength = points[0].getDistance(point);

                    // The length of the side is smaller than the requirement
                    if (sideLength < minimalLength)
                    {
                        break;
                    }

                    // Check if the third point (upper right) is a gaussian prime
                    if(!this->primalityTester->isGaussianPrime(point.translate(Direction::UP, sideLength)))
                    {
                        break;
                    }

                    // Check if the fourth point (upper left) is a gaussian prime
                    if(!this->primalityTester->isGaussianPrime(startingPoint.translate(Direction::UP, sideLength)))
                    {
                        break;
                    }
                }

                    // We have more than two sides, that means that we can compare the sides with eachother
                else if (points.size() > 2) {
                    // If the length of the last point to the previous point is not the
                    // Length of one of our sides, it is not a square
                    if (points[points.size() - 1].getDistance(points[points.size() - 2]) != sideLength) {
                        break;
                    }
                }

                // We have more points than a square should have
                if (points.size() >= 5) {
                    break;
                }
            }

            //Since we have found a point, we must change from direction
            switch(point.getDirection())
            {
                case Direction::UP:
                    point.setDirection(Direction::LEFT);
                    break;

                case Direction::LEFT:
                    point.setDirection(Direction::DOWN);
                    break;

                case Direction::DOWN:
                    point.setDirection(Direction::RIGHT);
                    break;

                case Direction::RIGHT:
                    point.setDirection(Direction::UP);
                    break;
            }
        }

        // Move one along
        point = point.translate(point.getDirection(), 1);
        length++;

    }

    this->length = length;
}

const Point &Path::getStartingPoint() const {
    return startingPoint;
}

void Path::setStartingPoint(const Point &startingPoint) {
    Path::startingPoint = startingPoint;
}

PrimalityTester * Path::getPrimalityTester() const {
    return this->primalityTester;
}

void Path::setPrimalityTester(PrimalityTester &primalityTester) {
    this->primalityTester = &primalityTester;
}

bool Path::isLoop() const {
    return loop;
}

bool Path::isSquare() const {
    return square;
}

int Path::getLength() const {
    return length;
}

Path::Path(const Point &startingPoint, PrimalityTester *primalityTester) : startingPoint(startingPoint), primalityTester(primalityTester) {

    this->startingPoint = startingPoint;
    this->primalityTester = primalityTester;
}

Path::Path() {}

const bool Path::operator<(const Path &path) const {

    // We are larger
    if(path.length < this->length)
    {
        return false;
    }

    // We are of the same length
    if(path.length == this->length)
    {
        Point origin = Point(0, 0);

        return path.getStartingPoint().getDistance(origin) < this->getStartingPoint().getDistance(origin);
    }

    return true;
}

int Path::getSideLength() const {
    return sideLength;
}
