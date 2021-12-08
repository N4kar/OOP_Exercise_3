#ifndef NSU_OOP_2021_LABS_WORKERWRITEFILE_H
#define NSU_OOP_2021_LABS_WORKERWRITEFILE_H

#include <fstream>

#include "Worker.h"

class WorkerWritefile : public Worker {
private:
    std::string filename;
public:
    static constexpr const char *WORKER_NAME = "writefile";

    WorkerWritefile(const unsigned workerId, WorkerArgs &args) : Worker(workerId) {
        this->assertNumberOfArgs(this->workerId, this->WORKER_NAME, 1, args.size());
        this->filename = args[0];
    }

    unsigned int getWorkerIOType() override {
        return Worker::WORKER_IO_TYPE_OUTPUT;
    }

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) {
        std::ofstream file;

        // enable exceptions
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        // opening the file
        try {
            file.open(this->filename);
        } catch (std::exception &exception) {
            throw WorkflowWorkerException(this->workerId, this->WORKER_NAME,
                                          "Error upon file opening. File not accessible?");
        }

        // writing to file
        try {
            for (auto &line: dataContainer->getLines()) {
                file << line << std::endl;
            }
        } catch (std::exception &exception) {
            throw WorkflowWorkerException(this->workerId, this->WORKER_NAME, "Error upon file reading.");
        }

        // closing the file
        try {
            file.close();
        } catch (std::exception &exception) {
            throw WorkflowWorkerException(this->workerId, this->WORKER_NAME, "Error upon closing the file.");
        }
    }
};


#endif // NSU_OOP_2021_LABS_WORKERWRITEFILE_H
