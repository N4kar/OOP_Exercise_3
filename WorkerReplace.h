#ifndef NSU_OOP_2021_LABS_WORKERREPLACE_H
#define NSU_OOP_2021_LABS_WORKERREPLACE_H

#include <algorithm>

#include "Worker.h"
#include "WorkflowSyntaxException.h"

class WorkerReplace : public Worker {
private:
    std::string needle;
    std::string replacement;

public:
    static constexpr const char *WORKER_NAME = "replace";

    WorkerReplace(const unsigned workerId, WorkerArgs &args) : Worker(workerId) {
        this->assertNumberOfArgs(this->workerId, this->WORKER_NAME, 2, args.size());
        this->needle = args[0];
        this->replacement = args[1];
    }

    unsigned int getWorkerIOType() override {
        return Worker::WORKER_IO_TYPE_INPUT_OUTPUT;
    }

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) {
        for (auto it = dataContainer->getLines().begin(); it != dataContainer->getLines().end(); ++it) {
            auto &line = *it;

            // @see https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
            size_t startPosition;
            do {
                startPosition = line.find(this->needle);
                if (startPosition != std::string::npos) {
                    line.replace(startPosition, this->needle.size(), this->replacement);
                }
            } while (startPosition != std::string::npos);
        }
    }
};


#endif // NSU_OOP_2021_LABS_WORKERREPLACE_H
