#ifndef NSU_OOP_2021_LABS_WORKFLOW_H
#define NSU_OOP_2021_LABS_WORKFLOW_H

#include <memory>
#include "Worker.h"
#include "WorkflowDataContainer.h"
#include "WorkflowLogicException.h"

class Workflow {
private:
    std::list<std::shared_ptr<Worker>> workers;
    std::list<std::shared_ptr<Worker>>::iterator currentWorker;
    std::shared_ptr<WorkflowDataContainer> dataContainer;
public:
    Workflow() {
        this->dataContainer = std::make_shared<WorkflowDataContainer>();
        this->currentWorker = workers.begin();
    }

    /**
     * Throws a WorkflowLogicException if impossible to enqueue the worker because of the IO context constraints
     * @param worker
     */
    void enqueueWorker(std::shared_ptr<Worker> &worker) {
        if (!this->workers.empty()) {
            auto lastWorkerIOType = this->workers.back()->getWorkerIOType();
            bool compatible;

            switch (worker->getWorkerIOType()) {
                case Worker::WORKER_IO_TYPE_INPUT:
                    compatible = lastWorkerIOType == Worker::WORKER_IO_TYPE_OUTPUT;
                    break;
                case Worker::WORKER_IO_TYPE_INPUT_OUTPUT:
                case Worker::WORKER_IO_TYPE_OUTPUT:
                    compatible = lastWorkerIOType != Worker::WORKER_IO_TYPE_OUTPUT;
                    break;
                default:
                    compatible = true;
            }

            if (!compatible) {
                throw WorkflowLogicException("Workflow error: worker \"%lu\" unexpected IO context. Check input, input-output and output connections between workers.", worker->getWorkerId());
            }
        }
        this->workers.push_back(worker);
        this->currentWorker = this->workers.begin();
    }

    std::shared_ptr<Worker> getCurrentWorker() {
        return *this->currentWorker;
    }

    void executeAndStepForward() {
        (*this->currentWorker)->execute(this->dataContainer);
        this->currentWorker++;
    }

    bool getAreAllWorkersExecuted() {
        return this->currentWorker == this->workers.end();
    }

    void clear() {
        this->workers.clear();
        this->currentWorker = workers.begin();
        this->dataContainer->getLines().clear();
    }
};

#endif // NSU_OOP_2021_LABS_WORKFLOW_H
