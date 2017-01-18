#ifndef PROJECT_WORKDIVIDER_H
#define PROJECT_WORKDIVIDER_H

#include <mutex>
#include "Point.h"

class WorkDivider {

private:
    std::tuple<Point, Point> work;

    int batchSize;

    int lastBatch = 0;
    std::mutex lastBatchMutex;

    std::mutex batchMutex;

public:
    WorkDivider(std::tuple<Point, Point> work, int batchSize=500);

    /**
     * Get the next batch of work
     * @return
     */
    std::tuple<int, int> getNextBatch();

    /**
     * Returns true if all the work has been handed out
     * @return
     */
    bool isFinished();

    /**
     * Get all the work that we have to do
     * @return
     */
    std::tuple<Point, Point> getWork() const;

    /**
     * Get the size of a single batch
     * @return
     */
    int getBatchSize() const;

    /**
     * Set the size of a single batch. WARNING: Do not call this method after we started giving out work
     * @param batchSize
     */
    void setBatchSize(int batchSize);

    /**
     * Get the index of the last batch we have handed out
     * @return
     */
    int getLastBatch();

    /**
     * Set the index of the last batch we have handed out
     * @param lastBatch
     */
    void setLastBatch(int lastBatch);
};


#endif //PROJECT_WORKDIVIDER_H
