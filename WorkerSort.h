#ifndef NSU_OOP_2021_LABS_WORKERSORT_H
#define NSU_OOP_2021_LABS_WORKERSORT_H

#include <string>

#include "Worker.h"
#include "WorkflowSyntaxException.h"

class WorkerSort : public Worker {
private:

public:
    static constexpr const char *
    WORKER_NAME = "sort";

    WorkerSort(const unsigned workerId, WorkerArgs &args) : Worker(workerId) {
        this->assertNumberOfArgs(this->workerId, this->WORKER_NAME, 0, args.size());
    }

    unsigned int getWorkerIOType() override {
        return Worker::WORKER_IO_TYPE_INPUT_OUTPUT;
    }

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) {
        dataContainer->getLines().sort(
                [](const std::string &a, const std::string &b) {
                    return a < b;
                }
        );
    }

};


#endif // NSU_OOP_2021_LABS_WORKERSORT_H
