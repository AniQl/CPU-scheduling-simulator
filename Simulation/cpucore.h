#ifndef CPUCORE_H
#define CPUCORE_H

#include <vector>
#include <map>

#include "simprocess.h"

class CPUCore
{
  public:
    CPUCore();
    ~CPUCore();

    void assignProcess( Process *pPtr, int currentTime );
    void removeProcess();
    Process* getCurrentProcess();
    int getLoadTime();
    int getUtilizationTime(int elapsedTime);
    bool isBusy();

  private:
    int loadTime;
    int busySince;
    bool CPUBusy;
    Process *cPtr; // current process pointer
};

#endif // CPUCORE_H
