#ifndef NSU_OOP_2021_LABS_WORKFLOWLOGICEXCEPTION_H
#define NSU_OOP_2021_LABS_WORKFLOWLOGICEXCEPTION_H

#include "WorkflowBaseException.h"

class WorkflowLogicException : public WorkflowBaseException {
public:
    WorkflowLogicException(const char *message) :
            WorkflowBaseException("Workflow logic error: %s", message) {
    }


    // @see https://www.geeksforgeeks.org/variadic-function-templates-c/
    template<typename ...TArgs>
    WorkflowLogicException(const char *format, TArgs ...args) :
            WorkflowBaseException(format, args...) {
    }
};

#endif //NSU_OOP_2021_LABS_WORKFLOWLOGICEXCEPTION_H
