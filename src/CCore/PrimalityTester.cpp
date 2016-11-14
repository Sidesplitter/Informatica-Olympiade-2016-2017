#include <random>
#include "PrimalityTester.h"

bool PrimalityTester::isPrime(uint32_t number, PrimalityMethod primalityMethod) {

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

    switch(primalityMethod)
    {
        case FERMAT:
            isPrime = this->isMillerRabinPrime(number);
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

const bool PrimalityTester::isMillerRabinPrime(const uint32_t number, const int precision) const {

    if(number <= 3)
    {
        return true;
    }

    if(!(number & 1))
    {
        return false;
    }

    int d = number - 1;
    int s = 0;

    // Continue while D is even
    while(d % 2 == 0)
    {
        d = d >> 1;
        s++;
    }

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(2, number - 2);

    for(int i = 0; i < precision; i++)
    {
        int a = distribution(generator);

        uint64_t x = pow_mod((uint64_t) a, (uint64_t) d, (uint64_t) number);

        if(x == 1 || x == number - 1)
        {
            continue;
        }

        for(int j = 0; j < s; j++)
        {
            x = pow_mod(x, 2, (uint64_t) number);

            if(x == 1)
            {
                return false;
            }

            if(x == number - 1)
            {
                break;
            }
        }

        if(x != number - 1) {
            return false;
        }
    }

    return true;

}

bool PrimalityTester::isGaussianPrime(int x, int y, PrimalityMethod primalityMethod) {

    if(x == 0)
    {
        if(y % 4 != 3)
        {
            return false;
        }

        return this->isPrime((uint32_t) y, primalityMethod);
    }

    if(y == 0)
    {
        if(x % 4 != 3)
        {
            return false;
        }

        return this->isPrime((uint32_t) x, primalityMethod);
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

    return this->isPrime(xSquared + ySquared, primalityMethod);
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

bool PrimalityTester::isGaussianPrime(const Point point, PrimalityTester::PrimalityMethod primalityMethod) {
    return this->isGaussianPrime(point.getX(), point.getY(), primalityMethod);
}

PrimalityTester::PrimalityTester() {}

bool PrimalityTester::isUsingCache() const {
    return cache;
}

void PrimalityTester::useCache(bool cache) {
    PrimalityTester::cache = cache;
}
