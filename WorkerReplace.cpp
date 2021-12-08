#include "WorkerReplace.h"
#include "WorkerCreatorConcrete.h"

static WorkerCreatorConcrete<WorkerReplace>creator(WorkerReplace::WORKER_NAME);