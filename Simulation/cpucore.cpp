#include "cpucore.h"

CPUCore :: CPUCore()
{
    loadTime = 0;
    busySince = 0;
    cPtr = nullptr;
    CPUBusy = false;
}

CPUCore ::  ~CPUCore()
{

}

void CPUCore :: assignProcess( Process *pPtr, int currentTime )
{
    CPUBusy = true;
    cPtr = pPtr;
    busySince = currentTime;
    cout << cPtr << " is being executed by CPU" << endl;
}

void CPUCore :: removeProcess()
{
    if ( cPtr->getIODelay() == 0 )
        loadTime += cPtr->getCPUTime();
    else
    {
        if ( cPtr->getState() == IO )
            loadTime += cPtr->getIODelay();
        else
            loadTime += cPtr->getCPUTime() - cPtr->getIODelay();
    }
    CPUBusy = false;
    cPtr = nullptr;
}

Process* CPUCore :: getCurrentProcess()
{
    return cPtr;
}

int CPUCore :: getLoadTime()
{
    return loadTime;
}

int CPUCore :: getUtilizationTime(int elapsedTime)
{
    if (CPUBusy)
        loadTime += elapsedTime - busySince;
    return loadTime;
}

bool CPUCore :: isBusy()
{
    return CPUBusy;
}


