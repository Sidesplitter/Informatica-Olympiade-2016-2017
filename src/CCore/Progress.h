//
// Created by jord on 19-11-16.
//

#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_PROGRESS_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_PROGRESS_H


#include <mutex>
#include <thread>

class Progress {

private:
    int maxProgress = 0;
    int currentProgress = 0;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::mutex progressMutex;
    std::thread drawThread;
    std::mutex drawMutex;
    bool run = false;

    void draw();

    /**
     * Formats the Eta in a [x]h[y]m[z]s format
     * @param eta
     * @return
     */
    std::string formatETA(std::chrono::duration<double> eta);

public:

    /**
     * Start the printing of progress to std::cout. The progress is displayed once per second
     */
    void start();

    /**
     * Stop the printing of progress to std::cout
     */
    void stop();

    /**
     * Increase the progress by one. This method is threadsafe
     */
    void increaseProgress();

    /**
     * Decrease the progress by one. This method is threadsafe
     */
    void decreaseProgress();

    /**
     * Set the progress. This method is threadsafe.
     * @param progress
     */
    void setProgress(const int progress);

    /**
     * Gets the progress. This method is threadsafe
     * @return
     */
    int getProgress();

    /**
     * Returns the current progress as a percentage. This method is threadsafe
     * @return
     */
    float getCurrentProgressPercentage();

    /**
     * Returns the estimated time it still takes based on the amount that is already done. This method is threadsafe
     * @return
     */
    std::chrono::duration<double> getEta();

    /**
     * Returns the maximum progress (the expected amount to process). This method is threadsafe
     * @return
     */
    int getMaxProgress();

    /**
     * Set the maximum progress (the expected amount to process). This method is threadsafe
     * @param maxProgress
     */
    void setMaxProgress(int maxProgress);
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_PROGRESS_H
