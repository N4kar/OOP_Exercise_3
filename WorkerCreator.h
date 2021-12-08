#ifndef NSU_OOP_2021_LABS_WORKERCREATOR_H
#define NSU_OOP_2021_LABS_WORKERCREATOR_H

#include <memory>
#include "Worker.h"

class WorkerCreator {
public:
    virtual std::shared_ptr<Worker> create(unsigned workerId, WorkerArgs &args) = 0;
};


#endif //NSU_OOP_2021_LABS_WORKERCREATOR_H
