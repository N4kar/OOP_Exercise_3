#ifndef NSU_OOP_2021_LABS_WORKFLOWRUNNER_H
#define NSU_OOP_2021_LABS_WORKFLOWRUNNER_H

#include <iostream>
#include <memory>
#include "Workflow.h"
#include "WorkflowConfigurationParser.h"
#include "WorkerFactory.h"

class WorkflowRunner {
protected:
    std::shared_ptr<WorkflowConfigurationParser> parser;
    std::shared_ptr<Workflow> workflow;

public:
    WorkflowRunner() {
        this->parser = std::make_shared<WorkflowConfigurationParser>();
        this->workflow = std::make_shared<Workflow>();
    }

    int runUsingTextFileConfiguration(const char *configurationFilename) {
        this->parser->clear();
        this->workflow->clear();

        // at first parse the configuration file
        try {
            std::cout << "Parsing the configuration" << std::endl;
            this->parser->loadFromFile(configurationFilename);
            std::cout << "Extracted configuration:" << std::endl
                      << this->parser->toString() << std::endl;
        } catch (WorkflowBaseException &exception) {
            std::cerr << "Exception while parsing the configuration: " << exception.what() << std::endl;
            return -1;
        }

        // once we have the configuration file we can create the workers
        std::cout << "Initializing the workflow" << std::endl;

        std::cout << "Initializing workers" << std::endl;
        for (auto const &blockId: this->parser->getBlocksOrder()) {
            std::cout << "Initializing worker " << blockId << std::endl;

            try {
                auto worker = WorkerFactory::getInstance().createWorker(blockId, this->parser->getBlocks().at(blockId));
                workflow->enqueueWorker(worker);
            } catch (WorkflowBaseException &exception) {
                std::cerr << "Exception while initializing workers: " << exception.what() << std::endl;
                return -1;
            }
        }

        // once workers are created we can execute the workflow
        try {
            std::cout << "Executing the workflow" << std::endl;
            while (!this->workflow->getAreAllWorkersExecuted()) {
                std::cout << "Executing worker " << this->workflow->getCurrentWorker()->getWorkerId() << std::endl;
                workflow->executeAndStepForward();
            }
            std::cout << "Execution finished" << std::endl;
        } catch (WorkflowLogicException &exception) {
            std::cerr << "Exception while executing the workflow: " << exception.what() << std::endl;
            return -1;
        }

        return 0;
    }
};


#endif //NSU_OOP_2021_LABS_WORKFLOWRUNNER_H
