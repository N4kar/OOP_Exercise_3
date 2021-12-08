#include <memory>
#include "WorkflowRunner.h"

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " workflow-filename" << std::endl;
        return -1;
    }

    const char *filename = argv[1];

    auto workflowRunner = std::make_shared<WorkflowRunner>();

    return workflowRunner->runUsingTextFileConfiguration(filename);
}