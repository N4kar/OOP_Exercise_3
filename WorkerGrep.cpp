#include "WorkerGrep.h"
#include "WorkerCreatorConcrete.h"

static WorkerCreatorConcrete<WorkerGrep>creator(WorkerGrep::WORKER_NAME);