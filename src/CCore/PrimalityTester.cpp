#include <cmath>
#include "PrimalityTester.h"

bool PrimalityTester::isPrime(uint32_t number) {

    if(this->cache) {
        {
            std::unique_lock<std::mutex> lock(this->primeCacheMutex);
            std::map<uint32_t, bool>::iterator cache = this->primeCache.find(number);

            //The prime is already in the prime cache, just return that value
            if (cache != this->primeCache.end()) {
                return cache->second;
            }
        }
    }

    // Special cases
    if(number <= 3)
    {
        return true;
    }

    // An even number can never be prime
    if(!(number & 1))
    {
        return false;
    }


    if(number % 3 == 0)
    {
        return false;
    }

    // Any number larger than five that is divisible by five is not a prime
    if(number != 5 && number % 5 == 0)
    {
        return false;
    }

    bool isPrime;

    switch(this->getPrimalityMethod())
    {
        case FERMAT:
            isPrime = this->isFermatPrime(number);
            break;
        case MILLER_RABIN:
            isPrime = this->isMillerRabinPrime(number);
            break;

        default:
            throw std::invalid_argument("Unknown primality method");
    }


    if(this->cache) {
        {
            std::unique_lock<std::mutex> lock(this->primeCacheMutex);
            this->primeCache[number] = isPrime;
        }
    }

    return isPrime;
}

/**
 * Calculates a ^ x % n
 *
 * This function is from https://github.com/cslarsen/miller-rabin/blob/master/miller-rabin.cpp#L37.
 * The reason why we can't do std::pow(a, x) % n is that it will overflow for large numbers, resulting in a nagetive
 * number. Oh the joy C++ brings.
 *
 * @param a
 * @param x
 * @param n
 * @return
 */
uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
    /*
     * Note that this code is sensitive to overflowing for testing
     * of large prime numbers.  The `a*r´ and `a*a´ operations can
     * overflow.  One easy way of solving this is to use 128-bit
     * precision for calculating a*b % n, since the mod operator
     * should always get us back to 64bits again.
     *
     * You can either use GCC's built-in __int128_t or use
     *
     * typedef unsigned int uint128_t __attribute__((mode(TI)));
     *
     * to create a 128-bit datatype.
     */

    uint64_t r=1;

    while ( x ) {
        if ( (x & 1) == 1 )
            //r = (__int128_t)a*r % n; // Slow
            r = a*r % n;

        x >>= 1;
        //a = (__int128_t)a*a % n; // SLow
        a = a*a % n;
    }

    return r;
}

const bool isMillerRabinComposite(uint64_t a, uint64_t d, uint64_t number, uint64_t s)
{
    uint64_t x = pow_mod(a, d, number);
    uint64_t y;

    while (s) {
        y = (x * x) % number;
        if (y == 1 && x != 1 && x != number-1)
            return false;
        x = y;
        --s;
    }

    if (y != 1) {
        return false;
    }

    return true;

}

const bool PrimalityTester::isMillerRabinPrime(const uint32_t number) const {

    if (number <= 3) {
        return true;
    }

    if (!(number & 1)) {
        return false;
    }

    int d = number / 2;
    int s = 1;

    // Continue while D is even
    while (!(d & 1)) {
        d /= 2;
        s++;
    }

    // Depending on how large the number is, we only need to test for specific numbers

    if(number < 1373653) {
        return isMillerRabinComposite(2, (uint64_t) d, number, (uint64_t) s) &&
               isMillerRabinComposite(3, (uint64_t) d, number, (uint64_t) s);
    }

    if(number < 9080191) {
        return isMillerRabinComposite(31, (uint64_t) d, number, (uint64_t) s) &&
               isMillerRabinComposite(72, (uint64_t) d, number, (uint64_t) s);
    }

    if(number < 4759123141) {
        return isMillerRabinComposite(2, (uint64_t) d, number, (uint64_t) s) &&
               isMillerRabinComposite(7, (uint64_t) d, number, (uint64_t) s) &&
               isMillerRabinComposite(61, (uint64_t) d, number, (uint64_t) s);

    }

    //The number is larger than 2 * 6000 ^ 2 (The result that (6000, 6000) gives
    // => we do not need to calculate it anymore
    throw new std::runtime_error("Number is larger than allowed (2*6000^2");
}

bool PrimalityTester::isGaussianPrime(int x, int y) {

    if(x == 0)
    {
        if(y % 4 != 3)
        {
            return false;
        }

        return this->isPrime((uint32_t) y);
    }

    if(y == 0)
    {
        if(x % 4 != 3)
        {
            return false;
        }

        return this->isPrime((uint32_t) x);
    }

    int xEven = !(x & 1);
    int yEven = !(y & 1);

    //Squares of even numbers remain even, and even + even = even. Even numbers can never be a prime
    //https://en.wikipedia.org/wiki/Square_number#Odd_and_even_square_numbers

    if(xEven && yEven)
    {
        return false;
    }

    //Squares of odd numbers remain odd and odd + odd = even. Even numbers can never be a prime
    //https://en.wikipedia.org/wiki/Square_number#Odd_and_even_square_numbers
    if(x > 2 && y > 2 && !xEven && !yEven)
    {
        return false;
    }

    uint32_t xSquared = (uint32_t) (x * x);
    uint32_t ySquared = (uint32_t) (y * y);

    return this->isPrime(xSquared + ySquared);
}

const bool PrimalityTester::isFermatPrime(const uint32_t number) const
{
    if(number <= 3)
    {
        return true;
    }

    if(!(number & 1))
    {
        return false;
    }

    return pow_mod(2, number - 1, number) == 1;
}

bool PrimalityTester::isGaussianPrime(const Point point) {
    return this->isGaussianPrime(point.getX(), point.getY());
}

PrimalityTester::PrimalityTester() {}

bool PrimalityTester::isUsingCache() const {
    return cache;
}

void PrimalityTester::useCache(bool cache) {
    PrimalityTester::cache = cache;
}

PrimalityTester::PrimalityMethod PrimalityTester::getPrimalityMethod() const {
    return primalityMethod;
}

void PrimalityTester::setPrimalityMethod(PrimalityTester::PrimalityMethod primalityMethod) {
    PrimalityTester::primalityMethod = primalityMethod;
}
