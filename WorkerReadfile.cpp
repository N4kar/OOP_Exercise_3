#include "WorkerReadfile.h"
#include "WorkerCreatorConcrete.h"

static WorkerCreatorConcrete<WorkerReadfile>creator(WorkerReadfile::WORKER_NAME);