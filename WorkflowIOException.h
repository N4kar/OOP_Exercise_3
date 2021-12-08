#ifndef NSU_OOP_2021_LABS_WORKFLOWIOEXCEPTION_H
#define NSU_OOP_2021_LABS_WORKFLOWIOEXCEPTION_H


#include "WorkflowBaseException.h"

class WorkflowIOException : public WorkflowBaseException {
public:
    WorkflowIOException(const char *message) :
            WorkflowBaseException("Input/output problem: %s", message) {

    }
};


#endif //NSU_OOP_2021_LABS_WORKFLOWIOEXCEPTION_H
