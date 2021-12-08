#ifndef CPP_LABS_WORKERREADFILE_H
#define CPP_LABS_WORKERREADFILE_H

#include        <fstream>

#include "Worker.h"
#include "WorkflowSyntaxException.h"

class WorkerReadfile : public Worker {
private:
    std::string filename;
public:
    static constexpr const char *WORKER_NAME = "readfile";

    WorkerReadfile(const unsigned workerId, WorkerArgs &args) : Worker(workerId) {
        this->assertNumberOfArgs(this->workerId, this->WORKER_NAME, 1, args.size());
        this->filename = args[0];
    }

    unsigned int getWorkerIOType() override {
        return Worker::WORKER_IO_TYPE_INPUT;
    }

    virtual void execute(std::shared_ptr<WorkflowDataContainer> dataContainer) {
        std::ifstream file;

        // enable exceptions
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        // opening the file
        try {
            file.open(this->filename);
        } catch (std::exception &exception) {
            throw WorkflowWorkerException(this->workerId, this->WORKER_NAME,
                                          "Error upon file opening. File not accessible or does not exist?");
        }

        // reading from file
        try {
            for (std::string line; std::getline(file, line);) {
                dataContainer->getLines().push_back(line);
            }
            // this line won't be reached because the very last getline will throw an exception
            // ->
        } catch (std::exception &exception) {
            // end-of-file throws an exception as well
            if (!file.eof()) {
                throw WorkflowWorkerException(this->workerId, this->WORKER_NAME, "Error upon file reading.");
            }
        }

        // closing the file
        try {
            file.close();
        } catch (std::exception &exception) {
            throw WorkflowWorkerException(this->workerId, this->WORKER_NAME, "Error upon closing the file.");
        }
    }
};


#endif //CPP_LABS_WORKERREADFILE_H
