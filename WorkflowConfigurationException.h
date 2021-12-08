#ifndef CPP_LABS_WORKFLOWCONFIGURATIONEXCEPTION_H
#define CPP_LABS_WORKFLOWCONFIGURATIONEXCEPTION_H

#include <string>
#include "WorkflowBaseException.h"

class WorkflowConfigurationException : public WorkflowBaseException {
private:
    const static int WHAT_MESSAGE_MAX_LENGTH = 255;
    char whatMessage[WHAT_MESSAGE_MAX_LENGTH];

public:
    WorkflowConfigurationException(const char *message) :
            WorkflowBaseException("Configuration error: %s", message) {
    }
};


#endif //CPP_LABS_WORKFLOWCONFIGURATIONEXCEPTION_H
