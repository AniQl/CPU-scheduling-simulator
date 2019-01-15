#ifndef CPUCORESUPERVISOR_H
#define CPUCORESUPERVISOR_H

#include "cpucore.h"

class CPUCoreSupervisor
{
  public:
    CPUCoreSupervisor( int CPUCount );
    ~CPUCoreSupervisor();

    void assignProcess( multimap<int, Process*> &queue, Process *pPtr, int currentTime );
    void removeProcess( Process *pPtr );
    int  getFreeSlots();
    string getUtilizationInfo(int elapsedTime);
    void clean();

  private:
    vector<CPUCore> cpus;
};

#endif // CPUCORESUPERVISOR_H
