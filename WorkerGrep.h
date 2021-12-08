#ifndef CPP_LABS_WORKERGREP_H
#define CPP_LABS_WORKERGREP_H

#include "Worker.h"
#include "WorkflowSyntaxException.h"

class WorkerGrep : public Worker {
private:
    std::string needle;

public:
    static constexpr const char *WORKER_NAME = "grep";

    WorkerGrep(const unsigned workerId, WorkerArgs &args) : Worker(workerId) {
        this->assertNumberOfArgs(this->workerId, this->WORKER_NAME, 1, args.size());
        this->needle = args[0];
    }

    unsigned int getWorkerIOType() override {
        return Worker::WORKER_IO_TYPE_INPUT_OUTPUT;
    }

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) {
        for (auto it = dataContainer->getLines().begin(); it != dataContainer->getLines().end();) {
            std::string &line = *it;
            if (line.find(this->needle) == std::string::npos) {
                // needle is not found
                it = dataContainer->getLines().erase(it);
            } else {
                ++it;
            }
        }
    }
};


#endif // NSU_OOP_2021_LABS_WORKERGREP_H
