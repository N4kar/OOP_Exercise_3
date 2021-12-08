#include "WorkerDump.h"
#include "WorkerCreatorConcrete.h"

static WorkerCreatorConcrete<WorkerDump>creator(WorkerDump::WORKER_NAME);