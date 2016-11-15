#include <iostream>
#include <future>
#include <cmath>
#include "CCore.h"


const std::vector<Point> CCore::getGaussianPrimes(const std::tuple<Point, Point> searchArea){


    std::vector<std::future<std::vector<Point>>> futures;

    // The amount of rows that each thread is going to do
    // ceil(Total rows / amount of threads)
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads());

    // Put the threads to work
    for(int i = 0; i < this->getThreads(); i++)
    {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getGaussianPrimesChunk,
                        this,
                        range,
                        searchArea
                ))
        );
    }

    std::vector<Point> points;

    // Collect the output
    for(int i = 0; i < futures.size(); i++)
    {
        std::vector<Point> foundPoints = futures[i].get();

        points.insert(points.end(), foundPoints.begin(), foundPoints.end());
    }

    return points;
}

const std::vector<Path> CCore::getSquares(const std::tuple<Point, Point> searchArea) {

    std::vector<Path> squares = {};

    std::vector<std::future<std::vector<Path>>> futures;
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads());

    for(int i = 0; i < this->getThreads(); i++)
    {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getSquareChunk,
                        this,
                        range,
                        searchArea
                ))
        );
    }

    for(int i = 0; i < futures.size(); i++)
    {
        std::vector<Path> foundSquares = futures[i].get();

        squares.insert(squares.end(), foundSquares.begin(), foundSquares.end());
    }

    return squares;
}

const Path CCore::getLargestSquare(const std::tuple<Point, Point> searchArea) {

    Path largestSquare = Path();

    std::vector<std::future<Path>> futures;
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads());

    for(int i = 0; i < this->getThreads(); i++)
    {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getLargestSquareChunk,
                        this,
                        range,
                        searchArea
                ))
        );
    }

    for(int i = 0; i < futures.size(); i++)
    {
        Path square = futures[i].get();

        largestSquare = std::max(square, largestSquare);
    }

    return largestSquare;
}

PrimalityTester * CCore::getPrimalityTester() const {
    return primalityTester;
}

void CCore::setPrimalityTester(PrimalityTester *primalityTester) {
    CCore::primalityTester = primalityTester;
}

const bool CCore::isPrime(const uint32_t number) {

    return this->primalityTester->isPrime(number);
}

CCore::CCore() {
    this->primalityTester =  new PrimalityTester();
}

std::vector<Point> CCore::getGaussianPrimesChunk(std::tuple<int, int> range,
                                   std::tuple<Point, Point> searchArea) {

    std::vector<Point> points;

    for(int y = std::get<0>(range); y < std::get<1>(range); y++)
    {
         for (int x = std::get<0>(searchArea).getX(); x < std::get<1>(searchArea).getX(); x++) {
             if (!this->primalityTester->isGaussianPrime(x, y)) {
                 continue;
             }

             points.push_back(Point(x, y));
         }
    }

    return points;
}

std::vector<Path> CCore::getSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);

    std::vector<Path> squares = {};

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++)
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

Path CCore::getLargestSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);

    Path largestSquare = Path();
    
    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++)
    {
        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea, true, largestSquare.getSideLength());

        if(!path.isSquare())
        {
            continue;
        }

        largestSquare = std::max(largestSquare, path);
    }

    return largestSquare;
}

int CCore::getThreads() const {
    return threads;
}

void CCore::setThreads(int threads) {
    CCore::threads = threads;
}

