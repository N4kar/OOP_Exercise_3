#ifndef NSU_OOP_2021_LABS_WORKERFACTORY_H
#define NSU_OOP_2021_LABS_WORKERFACTORY_H

#include <string>
#include <list>
#include <map>
#include <memory>

#include "WorkerDump.h"
#include "WorkerGrep.h"
#include "WorkerReadfile.h"
#include "WorkerReplace.h"
#include "WorkerSort.h"
#include "WorkerWritefile.h"
#include "WorkerCreator.h"

class WorkerFactory {
private:
    // singleton
    WorkerFactory() = default;

protected:
    std::map< std::string, WorkerCreator*> creators;

public:

    static WorkerFactory& getInstance() {
        static WorkerFactory singleton;
        return singleton;
    }

    void registerWorkerCreator(std::string workerName, WorkerCreator *creator) {
        this->creators[workerName] = creator;
    }

    std::shared_ptr<Worker> createWorker(const unsigned workerId, const std::vector<std::string> &words) {
        std::string workerName;
        std::vector<std::string> args;

        // split the words list into the worker name and its arguments
        int i = 0;
        for (auto it = words.begin(); it != words.end(); it++, i++) {
            if (i == 0) {
                workerName = *it;
            } else {
                args.push_back(*it);
            }
        }

        auto workerCreatorIterator = this->creators.find(workerName);
        if (workerCreatorIterator == this->creators.end()) {
            throw WorkflowSyntaxException("Unknown worker name");
        } else {
            auto workerCreatorPair = *workerCreatorIterator;
            return workerCreatorPair.second->create(workerId, args);
        }
    }

    // singleton
    WorkerFactory(const WorkerFactory& old) = delete;
    WorkerFactory& operator=(const WorkerFactory& old) = delete;
};


#endif // NSU_OOP_2021_LABS_WORKERFACTORY_H
