cmake_minimum_required(VERSION 3.17)
project(OOP_Exercise_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        OOP_Exercise_3
        main.cpp
        Worker.cpp
        Worker.h
        WorkerDump.cpp
        WorkerDump.h
        WorkerFactory.cpp
        WorkerFactory.h
        WorkerGrep.cpp
        WorkerGrep.h
        WorkerReadfile.cpp
        WorkerReadfile.h
        WorkerReplace.cpp
        WorkerReplace.h
        WorkerSort.cpp
        WorkerSort.h
        WorkerWritefile.cpp
        WorkerWritefile.h
        Workflow.cpp
        Workflow.h
        WorkflowBaseException.cpp
        WorkflowBaseException.h
        WorkflowConfigurationException.cpp
        WorkflowConfigurationException.h
        WorkflowConfigurationParser.cpp
        WorkflowConfigurationParser.h
        WorkflowParseException.cpp
        WorkflowParseException.h
        WorkflowSyntaxException.cpp
        WorkflowSyntaxException.h
        WorkflowWorkerException.cpp
        WorkflowWorkerException.h
        WorkflowDataContainer.cpp
        WorkflowDataContainer.h
        WorkflowLogicException.cpp
        WorkflowLogicException.h
        WorkflowRunner.cpp
        WorkflowRunner.h
        WorkerCreator.cpp
        WorkerCreator.h
        WorkerCreatorConcrete.cpp
        WorkerCreatorConcrete.h)