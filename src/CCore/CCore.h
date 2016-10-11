#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H

#include "Path.h"

class CCore {

private:
    PrimalityTester primalityTester;

public:
    /**
     * Get a list of gaussian primes in the given range
     * @param searchArea The first point should be the bottom left, the second point the top right
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return
     */
    const std::vector<Point> getGaussianPrimes(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod = PrimalityTester::PrimalityMethod::MILLER_RABIN);

    /**
     * Return all the squares in the given area
     *
     * @param searchArea The first point should be the bottom left, the second point the top right
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return A vector containing all the paths that are a square in the given search area
     */
    const std::vector<Path> getSquares(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod = PrimalityTester::PrimalityMethod::MILLER_RABIN);

    /**
     * Returns the largest square in the given area
     *
     * @param searchAreaThe first point should be the bottom left, the second point the top right
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return The path that is the largest square in the given search area
     */
    const Path getLargestSquare(const std::tuple<Point, Point> searchArea, PrimalityTester::PrimalityMethod primalityMethod = PrimalityTester::PrimalityMethod::MILLER_RABIN);

    /**
     * Checks if the given number is a prime or not a prime
     * @param number The number to check
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return True if the number is a prime, false if it is not
     */
    const bool isPrime(const uint32_t number, PrimalityTester::PrimalityMethod primalityMethod = PrimalityTester::PrimalityMethod::MILLER_RABIN);

    const PrimalityTester &getPrimalityTester() const;


    void setPrimalityTester(const PrimalityTester &primalityTester);
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_CCORE_H
