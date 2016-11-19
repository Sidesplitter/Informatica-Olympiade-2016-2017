#include <iostream>
#include <future>
#include <cmath>
#include "CCore.h"

const std::vector<Point> CCore::getGaussianPrimes(const std::tuple<Point, Point> searchArea, Progress *progress) {


    std::vector<std::future<std::vector<Point>>> futures;

    if (progress != nullptr) {
        progress->setMaxProgress(
                progress->getMaxProgress() + std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY());
    }

    // The amount of rows that each thread is going to do
    // ceil(Total rows / amount of threads)
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) /
                        this->getThreads());

    // Put the threads to work
    for (int i = 0; i < this->getThreads(); i++) {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getGaussianPrimesChunk,
                        this,
                        range,
                        searchArea,
                        progress
                ))
        );
    }

    std::vector<Point> points;

    // Collect the output
    for (int i = 0; i < futures.size(); i++) {
        std::vector<Point> foundPoints = futures[i].get();

        points.insert(points.end(), foundPoints.begin(), foundPoints.end());
    }

    return points;
}

const std::vector<Path> CCore::getSquares(const std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Path> squares = {};

    std::vector<std::future<std::vector<Path>>> futures;
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) /
                        this->getThreads());

    for (int i = 0; i < this->getThreads(); i++) {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getSquareChunk,
                        this,
                        range,
                        searchArea,
                        progress
                ))
        );
    }

    for (int i = 0; i < futures.size(); i++) {
        std::vector<Path> foundSquares = futures[i].get();

        squares.insert(squares.end(), foundSquares.begin(), foundSquares.end());
    }

    return squares;
}

const Path CCore::getLargestSquare(const std::tuple<Point, Point> searchArea, Progress *progress) {

    Path largestSquare = Path();

    std::vector<std::future<Path>> futures;
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) /
                        this->getThreads());

    for (int i = 0; i < this->getThreads(); i++) {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getLargestSquareChunk,
                        this,
                        range,
                        searchArea,
                        progress
                ))
        );
    }

    for (int i = 0; i < futures.size(); i++) {
        Path square = futures[i].get();

        largestSquare = std::max(square, largestSquare);
    }

    return largestSquare;
}

PrimalityTester *CCore::getPrimalityTester() const {
    return primalityTester;
}

void CCore::setPrimalityTester(PrimalityTester *primalityTester) {
    CCore::primalityTester = primalityTester;
}

const bool CCore::isPrime(const uint32_t number) {

    return this->primalityTester->isPrime(number);
}

CCore::CCore() {
    this->primalityTester = new PrimalityTester();

#ifdef HUMAN_MESSAGES
    if (std::thread::hardware_concurrency() == 0) {
        std::cout << "WARNING: Could not determine the amount of cores, running in single core mode." << std::endl;
    }
#endif

    this->threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 1;
}

std::vector<Point> CCore::getGaussianPrimesChunk(std::tuple<int, int> range,
                                                 std::tuple<Point, Point> searchArea,
                                                 Progress *progress) {

    std::vector<Point> points;

    for (int y = std::get<0>(range); y < std::get<1>(range); y++) {
        for (int x = std::get<0>(searchArea).getX(); x < std::get<1>(searchArea).getX(); x++) {
            if (!this->primalityTester->isGaussianPrime(x, y)) {
                continue;
            }

            points.push_back(Point(x, y));
        }

        if (progress != nullptr) {

            std::async(std::launch::async, &Progress::increaseProgress, progress);
        }
    }

    return points;
}

std::vector<Path>
CCore::getSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);

    if (progress != nullptr) {
        progress->setMaxProgress(progress->getMaxProgress() + (int) primes.size());
    }

    std::vector<Path> squares = {};

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {
        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea, true);

        if (path.isSquare()) {
            squares.push_back(path);
        }

        if (progress != nullptr) {

            std::async(std::launch::async, &Progress::increaseProgress, progress);
        }


    }

    return squares;
}

Path CCore::getLargestSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);

    if (progress != nullptr) {

        progress->setMaxProgress(progress->getMaxProgress() + (int) primes.size());
    }

    Path largestSquare = Path();

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {
        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea, true, largestSquare.getSideLength());

        if (path.isSquare()) {
            largestSquare = std::max(largestSquare, path);
        }

        if (progress != nullptr) {

            std::async(std::launch::async, &Progress::increaseProgress, progress);
        }
    }

    return largestSquare;
}

int CCore::getThreads() const {
    return threads;
}

void CCore::setThreads(int threads) {
    CCore::threads = threads;
}

Path CCore::getLargestLoopChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);

    if (progress != nullptr) {
        progress->setMaxProgress(progress->getMaxProgress() + (int) primes.size());
    }

    Path largestPath = Path();

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {
        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea);

        if (path.isLoop()) {
            largestPath = std::max(largestPath, path);
        }

        if (progress != nullptr) {

            std::async(std::launch::async, &Progress::increaseProgress, progress);
        }
    }

    return largestPath;
}

const Path CCore::getLargestLoop(const std::tuple<Point, Point> searchArea, Progress *progress) {

    Path largestPath = Path();

    std::vector<std::future<Path>> futures;
    int amount = (int) (std::ceil(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) /
                        this->getThreads());

    for (int i = 0; i < this->getThreads(); i++) {
        std::tuple<int, int> range = std::make_tuple(
                std::get<0>(searchArea).getY() + i * amount,
                std::get<0>(searchArea).getY() + (i + 1) * amount
        );

        futures.push_back(
                std::async(std::launch::async, std::bind(
                        &CCore::getLargestLoopChunk,
                        this,
                        range,
                        searchArea,
                        progress
                ))
        );
    }

    //Get the results from all the chunks and retrieve the largest
    for (int i = 0; i < futures.size(); i++) {
        Path square = futures[i].get();

        largestPath = std::max(square, largestPath);
    }

    return largestPath;
}

