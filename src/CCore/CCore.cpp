#include "CCore.h"

const std::vector<Point> CCore::getGaussianPrimes(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod){

    std::vector<Point> points = std::vector<Point>();

    for(int x = std::get<0>(searchArea).getX(); x < std::get<1>(searchArea).getX(); x++)
    {
        for(int y = std::get<0>(searchArea).getY(); y < std::get<1>(searchArea).getY(); y++)
        {
            if(!this->primalityTester.isGaussianPrime(x, y, primalityMethod))
            {
                continue;
            }

            points.push_back(Point(x, y));
        }
    }

    return points;
}

const std::vector<Path> CCore::getSquares(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod) {

    std::vector<Point> gaussianPrimes = this->getGaussianPrimes(searchArea, primalityMethod);
    std::vector<Path> squares = {};

    for (std::vector<Point>::iterator iterator = gaussianPrimes.begin(); iterator != gaussianPrimes.end(); iterator++)
    {
        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea, true);

        if(!path.isSquare())
        {
            continue;
        }

        squares.push_back(path);
    }

    return squares;
}

const Path CCore::getLargestSquare(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod) {
    std::vector<Point> gaussianPrimes = this->getGaussianPrimes(searchArea, primalityMethod);
    Path largestSquare;
    int sideLength = 0;

    // Iterate through all the found gaussian prime coordinates
    for (std::vector<Point>::iterator iterator = gaussianPrimes.begin(); iterator != gaussianPrimes.end(); iterator++)
    {
        // Create a new path and calculate it
        Path path = Path(*iterator, this->primalityTester);

        // Calculate the path with the square optimizations
        path.calculatePath(searchArea, true, sideLength);

        // It is not a square, move on
        if(!path.isSquare())
        {
            continue;
        }

        // We found a larger square => Add it
        if(path.getLength() > largestSquare.getLength())
        {
            largestSquare = path;
            sideLength = path.getLength();
        }

        // If the squares are of the same length, we must add the square that is closer to the origin
        if(path.getLength() == largestSquare.getLength())
        {
            Point origin = Point(0, 0);

            if(path.getStartingPoint().getDistance(origin) < largestSquare.getStartingPoint().getDistance(origin))
            {
                largestSquare = path;
            }
        }

    }

    return largestSquare;
}

const PrimalityTester &CCore::getPrimalityTester() const {
    return primalityTester;
}

void CCore::setPrimalityTester(const PrimalityTester &primalityTester) {
    CCore::primalityTester = primalityTester;
}

const bool CCore::isPrime(const uint32_t number, PrimalityTester::PrimalityMethod primalityMethod) {

    return this->primalityTester.isPrime(number, primalityMethod);
}
