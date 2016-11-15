#include <time.h>
#include <stdio.h>

#include "../CCore/CCore.h"

/**
 *
 * @param primalityMethod
 * @return
 */
float runBasicPrimes(PrimalityTester::PrimalityMethod primalityMethod, bool cache)
{
    PrimalityTester *primalityTester = new PrimalityTester();
    primalityTester->useCache(cache);
    primalityTester->setPrimalityMethod(primalityMethod);

    std::time_t start = std::time(nullptr);

    for(int i = 0; i < 5000000; i++) {
        primalityTester->isPrime((uint32_t) i);
    }

    for(int i = 0; i < 5000000; i++) {
        primalityTester->isPrime((uint32_t) i);
    }

    return time(nullptr) - start;
}

/**
 * Returns how long it takes to calculate all the gaussian points between (0, 0) and (3000, 3000)
 * @param primalityMethod
 * @return The amount of clocks it took to run this method
 */
float runBasicGaussianPrimes(PrimalityTester::PrimalityMethod primalityMethod, bool cache, int threads = 1)
{
    CCore cCore = CCore();
    cCore.setThreads(threads);
    cCore.getPrimalityTester()->useCache(cache);
    cCore.getPrimalityTester()->setPrimalityMethod(primalityMethod);

    std::time_t start = time(nullptr);

    cCore.getGaussianPrimes(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ));

   return time(nullptr) - start;
}

float runSquares(PrimalityTester::PrimalityMethod primalityMethod, bool cache, int threads = 1)
{
    CCore cCore = CCore();
    cCore.setThreads(threads);
    cCore.getPrimalityTester()->useCache(cache);
    cCore.getPrimalityTester()->setPrimalityMethod(primalityMethod);

    std::time_t start = time(nullptr);

    cCore.getSquares(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ));

    return time(nullptr) - start;
}

float runLargestSquare(PrimalityTester::PrimalityMethod primalityMethod, bool cache, int threads = 1)
{
    CCore cCore = CCore();
    cCore.setThreads(threads);
    cCore.getPrimalityTester()->useCache(cache);
    cCore.getPrimalityTester()->setPrimalityMethod(primalityMethod);

    std::time_t start = time(nullptr);

    cCore.getLargestSquare(std::make_tuple(
            Point(0, 0),
            Point(3000, 3000)
    ));

    return time(nullptr) - start;
}

void runTests(bool cache)
{
    int threads = std::thread::hardware_concurrency();

    /* Basic Primality Test */
    printf("*** Primality Test (2x 5000000 numbers) ***\n");
    printf("\tFermat: %.0fs\n", runBasicPrimes(PrimalityTester::FERMAT, cache));
    printf("\tMiller Rabin: %.0fs\n", runBasicPrimes(PrimalityTester::MILLER_RABIN, cache));

    /* Gaussian Primality Test */
    printf("\n*** Gaussian Primality Test - 1 Thread (3000x3000) *** \n");
    printf("\tFermat: %.0fs\n", runBasicGaussianPrimes(PrimalityTester::FERMAT, cache));
    printf("\tMiller Rabin: %.0fs\n", runBasicGaussianPrimes(PrimalityTester::MILLER_RABIN, cache));

    if(threads > 1)
    {
        printf("\n*** Gaussian Primality Test - %d Threads (3000x3000) *** \n", threads);
        printf("\tFermat: %.0fs\n", runBasicGaussianPrimes(PrimalityTester::FERMAT, cache, threads));
        printf("\tMiller Rabin: %.0fs\n", runBasicGaussianPrimes(PrimalityTester::MILLER_RABIN, cache, threads));
    }

    /* Square Test */
    printf("\n*** Square Test (3000x3000) - 1 Thread *** \n");
    printf("\tFermat: %.0fs\n", runSquares(PrimalityTester::FERMAT, cache));
    printf("\tMiller Rabin: %.0fs\n", runSquares(PrimalityTester::MILLER_RABIN, cache));

    if(threads > 1)
    {
        printf("\n*** Square Test (3000x3000) - %d Threads *** \n", threads);
        printf("\tFermat: %.0fs\n", runSquares(PrimalityTester::FERMAT, cache, threads));
        printf("\tMiller Rabin: %.0fs\n", runSquares(PrimalityTester::MILLER_RABIN, cache, threads));
    }

    /* Largest Square test */
    printf("\n*** Largest Square Test (3000x3000) - 1 Thread *** \n");
    printf("\tFermat: %.0fs\n", runLargestSquare(PrimalityTester::FERMAT, cache));
    printf("\tMiller Rabin: %.0fs\n", runLargestSquare(PrimalityTester::MILLER_RABIN, cache));

    if(threads > 1)
    {
        printf("\n*** Largest Square Test (3000x3000) - %d Threads *** \n", threads);
        printf("\tFermat: %.0fs\n", runLargestSquare(PrimalityTester::FERMAT, cache, threads));
        printf("\tMiller Rabin: %.0fs\n", runLargestSquare(PrimalityTester::MILLER_RABIN, cache, threads));
    }
}
int main()
{
    printf("===== Without Cache =====\n");
    runTests(false);

    printf("\n\n===== With Cache =====\n");
    runTests(true);

}