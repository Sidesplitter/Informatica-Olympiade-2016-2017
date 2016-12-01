#include <cmath>
#include <sstream>
#include <iostream>
#include "Progress.h"

void Progress::increaseProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress++;
    }
}

void Progress::decreaseProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress--;
    }
}

void Progress::setProgress(const int progress) {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress = progress;
    }
}

int Progress::getProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        return this->currentProgress;
    }
}


float Progress::getCurrentProgressPercentage() {


    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        return (float) this->currentProgress / this->maxProgress * 100;
    }

}

std::chrono::duration<double> Progress::getEta() {

    {
        int currentProgress =  this->currentProgress != 0 ? this->currentProgress : 1;

        std::unique_lock<std::mutex> lock(this->progressMutex);

        // Time taken per line * amount of lines left
        return ((std::chrono::system_clock::now() - this->startTime) / currentProgress *
                (this->maxProgress - this->currentProgress));
    }
}
void Progress::draw() {


    printf("\r%i/%i, %.2f%%, ETA: %s",
           this->getProgress(),
           this->getMaxProgress(),
           this->getCurrentProgressPercentage(),
           this->formatETA(this->getEta()).c_str()
    );

    fflush(stdout);
}

int Progress::getMaxProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        return maxProgress;
    }
}

void Progress::setMaxProgress(int maxProgress) {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->maxProgress = maxProgress;

    }
}

std::string Progress::formatETA(std::chrono::duration<double> eta) {

     //Format time
    int seconds = (int) this->getEta().count();
    std::string out;

    //Hours
    if (seconds / 3600 >= 1)
    {
        out += std::to_string((int) std::floor( seconds / 3600)) + "h";
        seconds = seconds % 3600;
    }

    //Minutes
    if(seconds / 60 >= 1)
    {
        out += std::to_string((int) std::floor(seconds/60)) + "m";
        seconds = seconds % 60;
    }

    out += std::to_string(seconds) + "s";

    return out;
}

void Progress::start() {

    this->startTime = std::chrono::system_clock::now();
    this->run = true;

    //Draw the progress every second, but do it in a separate thread
    this->drawThread = std::thread([this](){

        while(true)
        {
            //Check whether we should still be running
            {
                std::unique_lock<std::mutex> lock(this->drawMutex);
                if(!this->run)
                {
                    break;
                }
            }
            this->draw();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

void Progress::stop() {

    {
        std::unique_lock<std::mutex> lock(this->drawMutex);
        this->run = false;
    }

    this->drawThread.join();

    //Draw it once more, to make sure it has at least been drawn once.
    this->draw();
    std::cout << "\n";
}
