#include <time.h>
#include <stdio.h>

#include "../CCore/CCore.h"

/**
 *
 * @param primalityMethod
 * @return
 */
float runBasicPrimes(PrimalityTester::PrimalityMethod primalityMethod)
{
    PrimalityTester cCore = PrimalityTester();

    clock_t start = clock();

    for(int i = 0; i < 100000; i++) {
        cCore.isPrime((uint32_t) i, primalityMethod);
    }

    return clock() - start;
}

/**
 * Returns how long it takes to calculate all the gaussian points between (0, 0) and (3000, 3000)
 * @param primalityMethod
 * @return The amount of clocks it took to run this method
 */
float runBasicGaussianPrimes(PrimalityTester::PrimalityMethod primalityMethod)
{
    CCore cCore = CCore();

    clock_t start = clock();

    cCore.getGaussianPrimes(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ), primalityMethod);

    return clock() - start;
}

float runSquares(PrimalityTester::PrimalityMethod primalityMethod)
{
    CCore cCore = CCore();

    clock_t start = clock();

    cCore.getSquares(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ), primalityMethod);

    return clock() - start;
}

float runLargestSquare(PrimalityTester::PrimalityMethod primalityMethod)
{
    CCore cCore = CCore();

    clock_t start = clock();

    cCore.getLargestSquare(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ), primalityMethod);

    return clock() - start;
}

int main()
{
    printf("*** Basic Primality Test (100000 numbers) ***\n");
    printf("\tFermat: %fs\n", runBasicPrimes(PrimalityTester::FERMAT) / CLOCKS_PER_SEC);
    printf("\tMiller Rabin: %fs\n", runBasicPrimes(PrimalityTester::MILLER_RABIN) / CLOCKS_PER_SEC);

    printf("\n*** Basic Gaussian Primality Test (3000x3000) *** \n");
    printf("\tFermat: %fs\n", runBasicGaussianPrimes(PrimalityTester::FERMAT) / CLOCKS_PER_SEC);
    printf("\tMiller Rabin: %fs\n", runBasicGaussianPrimes(PrimalityTester::MILLER_RABIN) / CLOCKS_PER_SEC);

    printf("\n*** Square Test (3000x3000) *** \n");
    printf("\tFermat: %fs\n", runSquares(PrimalityTester::FERMAT) / CLOCKS_PER_SEC);
    printf("\tMiller Rabin: %fs\n", runSquares(PrimalityTester::MILLER_RABIN) / CLOCKS_PER_SEC);

    printf("\n*** Largest Square Test (3000x3000) *** \n");
    printf("\tFermat: %fs\n", runLargestSquare(PrimalityTester::FERMAT) / CLOCKS_PER_SEC);
    printf("\tMiller Rabin: %fs\n", runLargestSquare(PrimalityTester::MILLER_RABIN) / CLOCKS_PER_SEC);

}