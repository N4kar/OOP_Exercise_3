#ifndef CPP_LABS_WORKER_H
#define CPP_LABS_WORKER_H

#include <string>
#include <vector>
#include <memory>

#include "WorkflowWorkerException.h"
#include "WorkflowDataContainer.h"

typedef std::vector<std::string> WorkerArgs;

class Worker {
private:
protected:
    unsigned workerId;

    void static
    assertNumberOfArgs(const unsigned workerId, const char *workerName, const unsigned expectedNumberOfArgs,
                       const unsigned actualNumberOfArgs) {
        if (expectedNumberOfArgs != actualNumberOfArgs) {
            throw WorkflowWorkerException(
                    "Worker %lu error: worker \"%s\" expected %lu argument(s) but received %lu.",
                    workerId, workerName, expectedNumberOfArgs, actualNumberOfArgs);
        }
    }

public:
    const static unsigned WORKER_IO_TYPE_INPUT = 1;
    const static unsigned WORKER_IO_TYPE_OUTPUT = 2;
    const static unsigned WORKER_IO_TYPE_INPUT_OUTPUT = 3;

    Worker(const unsigned workerId) {
        this->workerId = workerId;
    }

    virtual ~Worker() {}

    unsigned getWorkerId() const {
        return this->workerId;
    }

    virtual unsigned getWorkerIOType() = 0;

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) = 0;
};


#endif //CPP_LABS_WORKER_H
