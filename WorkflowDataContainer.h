#ifndef NSU_OOP_2021_LABS_WORKFLOWDATACONTAINER_H
#define NSU_OOP_2021_LABS_WORKFLOWDATACONTAINER_H

#include <list>
#include <string>

class WorkflowDataContainer {
private:
    std::list<std::string> lines;

public:
    std::list<std::string> &getLines() {
        return this->lines;
    }
};

#endif //NSU_OOP_2021_LABS_WORKFLOWDATACONTAINER_H
