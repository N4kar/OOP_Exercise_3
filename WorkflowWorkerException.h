#ifndef NSU_OOP_2021_LABS_WORKFLOWWORKEREXCEPTION_H
#define NSU_OOP_2021_LABS_WORKFLOWWORKEREXCEPTION_H

#include <cstdarg>
#include "WorkflowBaseException.h"

class WorkflowWorkerException : public WorkflowBaseException {
public:
    WorkflowWorkerException(const unsigned workerId, const char *workerName, const char *message) :
            WorkflowBaseException("Worker %lu %s error: %s", workerId, workerName, message) {
    }

    // @see https://www.geeksforgeeks.org/variadic-function-templates-c/
    template<typename ...TArgs>
    WorkflowWorkerException(const char *format, TArgs ...args) :
            WorkflowBaseException(format, args...) {
    }
};


#endif //NSU_OOP_2021_LABS_WORKFLOWWORKEREXCEPTION_H
