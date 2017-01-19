#include <cmath>
#include <sstream>
#include <iostream>
#include "Progress.h"

void Progress::increaseProgress(const int amount) {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress += amount;
    }
}

void Progress::decreaseProgress(const int amount) {

    {
        std::unique_lock<std::mutex> lock(this->progressMutex);
        this->currentProgress -= amount;
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
        std::unique_lock<std::mutex> lock(this->progressMutex);

        if(currentProgress == 0)
        {
            return std::chrono::duration<double>(0);
        }

        int currentProgress =  this->currentProgress != 0 ? this->currentProgress : 1;

        // Time taken per line * amount of lines left
        return ((std::chrono::system_clock::now() - this->startTime) / currentProgress *
                (this->maxProgress - this->currentProgress));
    }
}
void Progress::draw() {

    std::ostringstream output;
    output.precision(4);
    output << this->getProgress() << "/" << this->getMaxProgress() << ", "
           << this->getCurrentProgressPercentage() << "%, "
           << "ETA: " << this->formatETA(this->getEta());

    std::cout << "\r" << output.str();

    // If the new progress message is shorter than the old one, it might happen that a part of the message remains on
    // the screen. To fix this, a simple universal solution is to fill the part that will not be overwritten with blanks
    unsigned long diff = this->previousProgress.length() - output.str().length();
    if(diff < 0){
        std::cout << std::string(" ", diff);
    }

    this->previousProgress = output.str();
    std::cout.flush();
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
#ifdef MULTI_THREADING
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
#endif
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
