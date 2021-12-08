#ifndef CPP_LABS_WORKFLOWPARSEEXCEPTION_H
#define CPP_LABS_WORKFLOWPARSEEXCEPTION_H

#include "WorkflowBaseException.h"

class WorkflowParseException : public WorkflowBaseException {
public:
    WorkflowParseException(const unsigned currentLine, const char *details) :
            WorkflowBaseException("Parsing error on line %lu: %s", currentLine, details) {
    }
};

#endif //CPP_LABS_WORKFLOWPARSEEXCEPTION_H
