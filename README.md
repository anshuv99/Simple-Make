# 537make

A build tool to read, validate and execute make files.
Uses fork and execvp for creation of new processes and command execution.

## Valgrind Task List

* **Fixed Issues**

* *driver.c*:15 
    * Issue: Definitely lost memory
    * Fix: freeing the memory allocated for the data structure used for parsing command line arguments.
    
* *entities/graph.c*:23
    * Issue: Uninitialised memory
    * Fix: Replacing malloc with calloc so that variable is always initialised.
    
* *input_parser/reader.c*:109-113
    * Issue: Definitely lost memory
    * Fix: freeing the memory allocated for the string used for parsing target names.
    
* *input_parser/reader.c*:184-223 
    * Issue: Definitely lost memory
    * Fix: freeing the memory allocated for the all the graph nodes and internal linked lists.
    
* *utils/validator.c*:23
    * Issue: Uninitialised memory
    * Fix: Replacing malloc with calloc so that variable is always initialised.

## Task List

This project is divided in the following major modules.

* **Input Parser**: 
    * Reads the command line arguments if passed and parses them.
    * Reads the make file and parses to create a graph structure for all the targets which are to be executed.

* **Target Executor**:
    * Traverses through the graph (assuming no cycles) in PostOrder manner.
    * Checks if a target requires rebuilt as per the modification time of all its dependencies.
    * Executes all the commands associated with a target if target building is required.

* **Entities**:
    * Graph:
        * It defines all the target node in the makeFile. All the dependencies and command associates are part of this structure.
        * It also provides following functionality.
        * This also lets you create all the connections among graph Node.
        * It also has cycle detection method
    
    * linkedList:
        * It defines the list of dependencies associated with TargetNode.
        * All the commands node are also modeled as linkedList
    
    * struct_input:
        * This input structure stores the input commands like target or makefile provided in the command line.
    
* **Utils**: 
    * Constants used across the program.
    * Validator used across the program.

* **driver.c** is the driver module for the entire project.

## Authors

* **Arpit Jain**
* **Anshu Verma**
