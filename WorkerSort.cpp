#include "WorkerSort.h"
#include "WorkerCreatorConcrete.h"

static WorkerCreatorConcrete<WorkerSort>creator(WorkerSort::WORKER_NAME);