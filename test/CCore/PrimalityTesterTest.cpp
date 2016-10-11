#include <gtest/gtest.h>
#include "CCore/PrimalityTester.h"

class PrimalityTesterTest : public ::testing::Test
{
protected:
    PrimalityTester primalityTester;

    virtual void SetUp()
    {
        primalityTester = PrimalityTester();
    }
};


TEST_F(PrimalityTesterTest, PrimalityTesterTestMillerRabinPrime)
{
    EXPECT_FALSE(primalityTester.isMillerRabinPrime(4));
    EXPECT_TRUE(primalityTester.isMillerRabinPrime(5));
}

TEST_F(PrimalityTesterTest, PrimalityTesterTestFermatPrime)
{
    EXPECT_FALSE(primalityTester.isFermatPrime(4));
    EXPECT_TRUE(primalityTester.isFermatPrime(5));
}

TEST_F(PrimalityTesterTest, PrimalityTesterTestPrime)
{
    EXPECT_TRUE(primalityTester.isPrime(1));
    EXPECT_TRUE(primalityTester.isPrime(2));
    EXPECT_TRUE(primalityTester.isPrime(3));
    EXPECT_FALSE(primalityTester.isPrime(4));
    EXPECT_TRUE(primalityTester.isPrime(5));
}

TEST_F(PrimalityTesterTest, PrimalityTesterTestGuassianPrime)
{
    EXPECT_TRUE(primalityTester.isGaussianPrime(1, 1));
    EXPECT_FALSE(primalityTester.isGaussianPrime(2, 2));
    EXPECT_TRUE(primalityTester.isGaussianPrime(4, 5));
    EXPECT_FALSE(primalityTester.isGaussianPrime(4, 7));
    EXPECT_FALSE(primalityTester.isGaussianPrime(7, 13));
    EXPECT_FALSE(primalityTester.isGaussianPrime(8, 4));
    EXPECT_TRUE(primalityTester.isGaussianPrime(12, 7));
    EXPECT_FALSE(primalityTester.isGaussianPrime(14, 7));
    EXPECT_TRUE(primalityTester.isGaussianPrime(14, 15));
}