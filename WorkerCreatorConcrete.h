//
// Created by Nakar on 08.12.2021.
//

#ifndef NSU_OOP_2021_LABS_WORKERCREATORCONCRETE_H
#define NSU_OOP_2021_LABS_WORKERCREATORCONCRETE_H

#include "Worker.h"
#include "WorkerCreator.h"
#include "WorkerFactory.h"

template<typename T>
class WorkerCreatorConcrete: public WorkerCreator {
public:
    std::shared_ptr<Worker> create(unsigned workerId, WorkerArgs &args) {
        return std::make_shared<T>(workerId, args);
    }

    WorkerCreatorConcrete(std::string workerName) {
        WorkerFactory::getInstance().registerWorkerCreator(workerName, this);
    }
};


#endif //NSU_OOP_2021_LABS_WORKERCREATORCONCRETE_H
