#include "WorkDivider.h"

WorkDivider::WorkDivider(std::tuple<int, int> work, int batchSize) : work(work), batchSize(batchSize) {}

std::tuple<int, int> WorkDivider::getWork() const {
    return work;
}

int WorkDivider::getBatchSize() const {
    return batchSize;
}
int WorkDivider::getLastBatch() {
    std::unique_lock<std::mutex> lock(this->lastBatchMutex);
    return lastBatch;
}

void WorkDivider::setLastBatch(int lastBatch) {
    std::unique_lock<std::mutex> lock(this->lastBatchMutex);
    WorkDivider::lastBatch = lastBatch;
}

std::tuple<int, int> WorkDivider::getNextBatch() {
    std::unique_lock<std::mutex> lock(this->batchMutex);

    int nextBatch = this->getLastBatch() + 1;
    this->setLastBatch(nextBatch);
    return std::make_tuple(
                std::get<0>(work) + (nextBatch - 1) * getBatchSize(),
                std::min(std::get<0>(work) + nextBatch * getBatchSize(), std::get<1>(work))
    );
}

bool WorkDivider::isFinished() {

    return std::get<0>(work) + this->getLastBatch() * getBatchSize() >= std::get<1>(work);
}

void WorkDivider::setBatchSize(int batchSize) {
    WorkDivider::batchSize = batchSize;
}
