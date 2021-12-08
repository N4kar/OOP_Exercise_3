#ifndef NSU_OOP_2021_LABS_WORKFLOWSYNTAXEXCEPTION_H
#define NSU_OOP_2021_LABS_WORKFLOWSYNTAXEXCEPTION_H

#include "WorkflowBaseException.h"

class WorkflowSyntaxException : public WorkflowBaseException {
public:
    WorkflowSyntaxException(const char *message) :
            WorkflowBaseException("Syntax error: %s", message) {
    }
};


#endif //NSU_OOP_2021_LABS_WORKFLOWSYNTAXEXCEPTION_H
