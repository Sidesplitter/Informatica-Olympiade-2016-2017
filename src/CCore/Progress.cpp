#include <cmath>
#include <sstream>
#include <iostream>
#include "Progress.h"

Progress::Progress() {

    this->startTime = std::chrono::system_clock::now();
}

void Progress::increaseProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress++;
    }

    draw();
}

void Progress::decreaseProgress() {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress--;
    }

    draw();
}

void Progress::setProgress(const int progress) {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress = progress;
    }

    draw();
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

    this->draw();
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
