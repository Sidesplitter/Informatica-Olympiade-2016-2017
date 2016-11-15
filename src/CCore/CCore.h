#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H

#include <thread>
#include "Path.h"

class CCore {

private:
    PrimalityTester *primalityTester;

    /**
     * Internally we devide the work into chunks
     * This function calculates all the gaussian primes
     * @param range The rows(Y) we need to calculate in this chunk, from low to high
     * @param searchArea The overal search area.
     * @return
     */
    std::vector<Point> getGaussianPrimesChunk(
            std::tuple<int, int> range,
            std::tuple<Point, Point> searchArea
    );

    std::vector<Path> getSquareChunk(
            std::tuple<int, int> range,
            std::tuple<Point, Point> searchArea
    );

    Path getLargestSquareChunk(
            std::tuple<int, int> range,
            std::tuple<Point, Point> searchArea
    );

    /**
     * The amount of threads used with calculations
     */
    int threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 1;
public:
    CCore();

    /**
     * Get a list of gaussian primes in the given range
     * @param searchArea The first point should be the bottom left, the second point the top right
     * @return
     */
    const std::vector<Point> getGaussianPrimes(const std::tuple<Point, Point> searchArea);


    /**
     * Return all the squares in the given area
     *
     * @param searchArea The first point should be the bottom left, the second point the top right
     * @return A vector containing all the paths that are a square in the given search area
     */
    const std::vector<Path> getSquares(const std::tuple<Point, Point> searchArea);

    /**
     * Returns the largest square in the given area
     *
     * @param searchAreaThe first point should be the bottom left, the second point the top right
     * @return The path that is the largest square in the given search area
     */
    const Path getLargestSquare(const std::tuple<Point, Point> searchArea);

    /**
     * Checks if the given number is a prime or not a prime
     * @param number The number to check
     * @return True if the number is a prime, false if it is not
     */
    const bool isPrime(const uint32_t number);

    PrimalityTester * getPrimalityTester() const;


    void setPrimalityTester(PrimalityTester *primalityTester);

    /**
     * Get the amount of threads that will be used for calculations. The default is the amount of cores on your machine
     * if it can be detected with std::thread::hardware_concurrency(). If this is not the case it will be reduced to
     * only 1 thread by default.
     *
     * @return
     */
    int getThreads() const;

    void setThreads(int threads);
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H
