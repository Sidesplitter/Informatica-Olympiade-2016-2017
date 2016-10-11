#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_PATH_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_PATH_H

#include <tuple>
#include "Point.h"
#include "PrimalityTester.h"

class Path {

private:
    Point startingPoint;
    PrimalityTester primalityTester;
    bool loop = false;
    bool square = false;
    int length = 0;

public:

    Path(const Point &startingPoint, const PrimalityTester &primalityTester);

    /**
     *
     * @param searchArea
     * @param squareOptimization This speeds up the calculation, but might stop early if it is not a square.
     * @param minimalLength Only used when squareOptimization is on, this must be the minimal length of a side of the
     * square.
     * @param maximumPoints The maximum amount of gaussian points that we are calculating, zero means infinite.
     * If suareOptimalization is true this value will be overwritten.
     */
    void calculatePath(
            std::tuple<Point, Point> searchArea,
            bool squareOptimization = false,
            int minimalLength = 0,
            int maximumPoints = 0
    );

    const Point &getStartingPoint() const;

    void setStartingPoint(const Point &startingPoint);

    const PrimalityTester &getPrimalityTester() const;

    void setPrimalityTester(const PrimalityTester &primalityTester);

    bool isLoop() const;

    bool isSquare() const;

    int getLength() const;

    Path();
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_PATH_H
