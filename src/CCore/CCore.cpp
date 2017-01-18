#include <iostream>
#ifdef MULTI_THREADING
#include <thread>
#include <future>
#endif
#include <cmath>
#include "CCore.h"
#include "WorkDivider.h"
#include <algorithm>

const std::vector<Point> CCore::getGaussianPrimes(const std::tuple<Point, Point> searchArea, Progress *progress) {

#ifndef MULTI_THREADING
    // Single threaded mode, ignore complex code
    return this->getGaussianPrimesChunk(
            std::make_tuple(std::get<0>(searchArea).getY(), std::get<1>(searchArea).getY()),
            searchArea,
            progress
    );
#else
    std::vector<std::future<std::vector<Point>>> futures;

    if (progress != nullptr) {
        progress->setMaxProgress(
                progress->getMaxProgress() + std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY());

        progress->start();
    }

    WorkDivider * divider = new WorkDivider(searchArea);
    //If the range is relatively small, not all of our threads are being put to work
    //To fix this, we divide the amount of work by the amount of threads, but only if it is lower than the default
    //value.
    divider->setBatchSize(std::min(
            divider->getBatchSize(),
            (std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads()
    ));

    for (int i = 0; i < this->getThreads(); i++) {

        futures.push_back(
                std::async(std::launch::async, [this, divider, searchArea, progress](){

                    std::vector<Point> points = {};

                    while(!divider->isFinished()){
                        auto foundPoints = this->getGaussianPrimesChunk(divider->getNextBatch(), searchArea, progress);
                        points.insert(points.end(), foundPoints.begin(), foundPoints.end());
                    }

                    return points;
                })
        );
    }

    std::vector<Point> points;

    // Collect the output
    for (int i = 0; i < futures.size(); i++) {
        std::vector<Point> foundPoints = futures[i].get();

        points.insert(points.end(), foundPoints.begin(), foundPoints.end());
    }

    if (progress != nullptr) {

        progress->stop();
    }

    return points;
#endif
}

const std::vector<Path> CCore::getSquares(const std::tuple<Point, Point> searchArea, Progress *progress) {

#ifndef MULTI_THREADING
    // Single threaded mode, ignore complex code
    return this->getSquareChunk(
            std::make_tuple(std::get<0>(searchArea).getY(), std::get<1>(searchArea).getY()),
            searchArea,
            progress
    );
#else

    std::vector<std::future<std::vector<Path>>> futures;

    if(progress != nullptr)
    {
        progress->start();
    }

    WorkDivider * divider = new WorkDivider(searchArea);
    //If the range is relatively small, not all of our threads are being put to work
    //To fix this, we divide the amount of work by the amount of threads, but only if it is lower than the default
    //value.
    divider->setBatchSize(std::min(
            divider->getBatchSize(),
            (std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads()
    ));

    for (int i = 0; i < this->getThreads(); i++) {

        futures.push_back(
                std::async(std::launch::async, [this, divider, searchArea, progress](){

                    std::vector<Path> squares = {};

                    while(!divider->isFinished()){
                        auto foundSquares = this->getSquareChunk(divider->getNextBatch(), searchArea, progress);
                        squares.insert(squares.end(), foundSquares.begin(), foundSquares.end());
                    }

                    return squares;
                })
        );
    }

    std::vector<Path> squares = {};

    for (int i = 0; i < futures.size(); i++) {
        std::vector<Path> foundSquares = futures[i].get();

        squares.insert(squares.end(), foundSquares.begin(), foundSquares.end());
    }

    if(progress != nullptr)
    {
        progress->stop();
    }

    return squares;
#endif
}

const Path CCore::getLargestSquare(const std::tuple<Point, Point> searchArea, Progress *progress) {

#ifndef MULTI_THREADING
    // Single threaded mode, ignore complex code
    return this->getLargestSquareChunk(
            std::make_tuple(std::get<0>(searchArea).getY(), std::get<1>(searchArea).getY()),
            searchArea,
            progress
    );
#else

    std::vector<std::future<Path>> futures;

    if(progress != nullptr)
    {
        progress->setMaxProgress(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY());
        progress->start();
    }

    WorkDivider * divider = new WorkDivider(searchArea);
    //If the range is relatively small, not all of our threads are being put to work
    //To fix this, we divide the amount of work by the amount of threads, but only if it is lower than the default
    //value.
    divider->setBatchSize(std::min(
            divider->getBatchSize(),
            (std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads()
    ));

    for (int i = 0; i < this->getThreads(); i++) {

        futures.push_back(
                std::async(std::launch::async, [this, divider, searchArea, progress](){

                    Path square;

                    while(!divider->isFinished()){
                        square = std::max(
                                square,
                                this->getLargestSquareChunk(divider->getNextBatch(), searchArea, progress)
                        );
                    }

                    return square;
                })
        );
    }

    Path largestSquare = Path();

    for (int i = 0; i < futures.size(); i++) {
        Path square = futures[i].get();

        largestSquare = std::max(square, largestSquare);
    }

    if(progress != nullptr)
    {
        progress->stop();
    }

    return largestSquare;
#endif
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

#ifndef MULTI_THREADING
    this->threads = 1;
#else
    #ifdef HUMAN_MESSAGES
        if (std::thread::hardware_concurrency() == 0) {
            std::cout << "WARNING: Could not determine the amount of cores, running in single threaded mode."
                      << std::endl;
        }
    #endif

    this->threads = std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 1;
#endif

    this->getPrimalityTester()->useCache(this->threads == 1);
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

#ifdef MULTI_THREADING
        if (progress != nullptr) {

            std::async(std::launch::async, &Progress::increaseProgress, progress, 1);
        }
#endif
    }

    return points;
}

std::vector<Path>
CCore::getSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);
    std::vector<int> passedY = {};
    
    if (progress != nullptr) {
        progress->setMaxProgress(progress->getMaxProgress() + (int) primes.size());
    }

    std::vector<Path> squares = {};

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {
        Point prime = *iterator;
        Path path = Path(prime, this->primalityTester);

        path.calculatePath(searchArea, true);

        if (path.isSquare()) {
            squares.push_back(path);
        }

#ifdef MULTI_THREADING
        if (progress != nullptr) {

            if(std::find(passedY.begin(), passedY.end(), prime.getY()) == passedY.end()){
                std::async(std::launch::async, &Progress::increaseProgress, progress, 1);
                passedY.push_back(prime.getY());
            }
        }
#endif
    }

    return squares;
}

Path CCore::getLargestSquareChunk(std::tuple<int, int> range, std::tuple<Point, Point> searchArea, Progress *progress) {

    std::vector<Point> primes = this->getGaussianPrimesChunk(range, searchArea);
    std::vector<int> passedY = {};
    Path largestSquare = Path();

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {
        Point prime = *iterator;
        Path path = Path(prime, this->primalityTester);

        path.calculatePath(searchArea, true, largestSquare.getSideLength());

        if (path.isSquare()) {
            largestSquare = std::max(largestSquare, path);
        }
        
        #ifdef MULTI_THREADING
        if (progress != nullptr) {

            if(std::find(passedY.begin(), passedY.end(), prime.getY()) == passedY.end()){
                std::async(std::launch::async, &Progress::increaseProgress, progress, 1);
                passedY.push_back(prime.getY());
            }
        }
        #endif
        
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
    std::vector<int> passedY = {};

    Path largestPath = Path();

    for (std::vector<Point>::iterator iterator = primes.begin(); iterator != primes.end(); iterator++) {

        Point prime = *iterator;

        Path path = Path(*iterator, this->primalityTester);

        path.calculatePath(searchArea);

        if (path.isLoop()) {
            largestPath = std::max(largestPath, path);
        }

#ifdef MULTI_THREADING
        if (progress != nullptr) {

            if(std::find(passedY.begin(), passedY.end(), prime.getY()) == passedY.end()){
                std::async(std::launch::async, &Progress::increaseProgress, progress, 1);
                passedY.push_back(prime.getY());
            }
        }
#endif
    }
    
    return largestPath;
}

const Path CCore::getLargestLoop(const std::tuple<Point, Point> searchArea, Progress *progress) {

#ifndef MULTI_THREADING
    return this->getLargestLoopChunk(
            std::make_tuple(std::get<0>(searchArea).getY(), std::get<1>(searchArea).getY()),
            searchArea,
            progress
    );
#else

    std::vector<std::future<Path>> futures;

    if(progress != nullptr)
    {
        progress->setMaxProgress(std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY());
        progress->start();
    }

    WorkDivider * divider = new WorkDivider(searchArea);
    //If the range is relatively small, not all of our threads are being put to work
    //To fix this, we divide the amount of work by the amount of threads, but only if it is lower than the default
    //value.
    divider->setBatchSize(std::min(
            divider->getBatchSize(),
            (std::get<1>(searchArea).getY() - std::get<0>(searchArea).getY()) / this->getThreads()
    ));

    for (int i = 0; i < this->getThreads(); i++) {

        futures.push_back(
                std::async(std::launch::async, [this, divider, searchArea, progress](){

                    Path largestPath;

                    while(!divider->isFinished()){
                        largestPath = std::max(
                                largestPath,
                                this->getLargestLoopChunk(divider->getNextBatch(), searchArea, progress)
                        );
                    }

                    return largestPath;
                })
        );
    }

    Path largestPath = Path();

    //Get the results from all the chunks and retrieve the largest
    for (int i = 0; i < futures.size(); i++) {
        Path square = futures[i].get();

        largestPath = std::max(square, largestPath);
    }

    if(progress != nullptr)
    {
        progress->stop();
    }

    return largestPath;
#endif
}

