#ifndef SIMPROCESS_H
#define SIMPROCESS_H

#include <stdlib.h>
#include <iostream>

#include "generator.h"

using namespace std;

//CP - process is created (create process)
//IO - process needs access to IO device (IO device)
//RC - process needs access to cpu (request core)
//FP - finish process lifecycle (finish process)
enum STATE {CP, IO, RC, FP};

class Process
{
  public:
    Process(int IODCount = 4, int simulationTime = 0);
   ~Process();

    int getCPUTime();   // cpu execution time
    int getIOID();      // IO device id required for process
    int getIODelay();   // delay before IO device is called
    int getIOOccupy();  // how long IO device is occupied
    int getCreationTime();  // when process was created
    int getExecutionTime(); // how long it takes to execute this process (ideal conditions)
    STATE getState();   // state of process
    int nextState();    // next state of process
    void getFullInfo(int delay);
    void getInfo(int delay);

  private:
    int CPUExecutionTime;
    int IODeviceID;
    int IODeviceDelay;
    int IODeviceOccupy;
    STATE state;
    int creationTime;
};

#endif // SIMPROCESS_H
