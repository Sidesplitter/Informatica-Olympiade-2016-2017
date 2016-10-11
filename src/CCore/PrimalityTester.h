#ifndef INFORMATICA_OLYMPIADE_2016_2017_CCORE_H
#define INFORMATICA_OLYMPIADE_2016_2017_CCORE_H

#include <map>
#include <vector>
#include "Point.h"

class PrimalityTester {

private:
    /**
     * The prime cache contains all the previously calculated numbers so that they do not have to be calculated again
     */
    std::map<uint32_t, bool> primeCache;

public:

    enum PrimalityMethod { FERMAT, MILLER_RABIN};

    /**
     * Checks if the given number is a check using the given method. This method contains some optimization and caching
     * and is faster than calling isMillerRabinPrime or isFermaPrime directly.
     *
     * @param number The number to check for primality
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return True if the number is a prime, false if not
     */
    bool isPrime(uint32_t number, PrimalityMethod primalityMethod = MILLER_RABIN);

    /**
     * Checks if the given numbers are a gaussian prime.
     *
     * @see http://mathworld.wolfram.com/GaussianPrime.html
     * @see https://en.wikipedia.org/wiki/Gaussian_integer
     *
     * @param x The first number to check
     * @param y The second number to check
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return True if the two numbers together are a gaussian prime, false if not.
     */
    bool isGaussianPrime(int x, int y, PrimalityMethod primalityMethod = MILLER_RABIN);

    /**
     * Checks if the given numbers are a gaussian prime.
     *
     * @see http://mathworld.wolfram.com/GaussianPrime.html
     * @see https://en.wikipedia.org/wiki/Gaussian_integer
     *
     * @param point The point to check
     * @param primalityMethod The primality method to use, defaults to Miller Rabin
     * @return True if the point is a gaussian prime, false if not
     */
    bool isGaussianPrime(const Point point, PrimalityMethod primalityMethod = MILLER_RABIN);

    /**
     * Check if the number is a prime according to the Miller Rabin primality test. This method is more accurate
     * than isFermatPrime but does take longer to calculate.
     *
     * @see https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
     * @param number The number to check
     * @param precision The amount of checks we put on the given number.
     * @return True if the number is a prime, false if not.
     */
    const bool isMillerRabinPrime(const uint32_t number, const int precision = 2) const;

    /**
     * Check if a number is a prime according to Fermat's little theorem. This can return true for some numbers
     * that are not primes. See isRabinMillerPrime for higher accuracy.
     *
     * @see https://en.wikipedia.org/wiki/Fermat%27s_little_theorem
     * @param number The number to check
     * @return True if the number is a prime, false if it is not.
     */
    const bool isFermatPrime(const uint32_t number) const;
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_CCORE_H
