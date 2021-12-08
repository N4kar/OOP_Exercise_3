#ifndef CPP_LABS_WORKFLOWBASEEXCEPTION_H
#define CPP_LABS_WORKFLOWBASEEXCEPTION_H

#include <string>
#include <exception>
#include <cstdarg>

class WorkflowBaseException : public std::exception {
private:
    const static int WHAT_MESSAGE_MAX_LENGTH = 255;
    char whatMessage[WHAT_MESSAGE_MAX_LENGTH];

public:
    WorkflowBaseException(const char *format, ...) {
        va_list args;
        va_start (args, format);
        vsnprintf(this->whatMessage, WHAT_MESSAGE_MAX_LENGTH, format, args);
        va_end (args);
    }

    const char *what() const noexcept {
        return this->whatMessage;
    }
};


#endif //CPP_LABS_WORKFLOWBASEEXCEPTION_H
