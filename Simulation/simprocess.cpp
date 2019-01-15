#include "simprocess.h"

Process ::  Process(int IODCount, int simulationTime)
{
    UniformGenerator ug(rand());
    CPUExecutionTime = ug.Rand(1, 50);
    IODeviceID = ug.Rand(0, IODCount-1);
    IODeviceDelay = ug.Rand(0, CPUExecutionTime-1);
    IODeviceOccupy = ug.Rand(1, 10);
    creationTime = simulationTime;
    state = CP;
}

Process :: ~Process()
{

}

int Process :: getCPUTime()
{
    return CPUExecutionTime;
}

int Process :: getIOID()
{
    return IODeviceID;
}

int Process :: getIODelay()
{
    return IODeviceDelay;
}

int Process :: getIOOccupy()
{
    return IODeviceOccupy;
}

int Process::getCreationTime()
{
    return creationTime;
}

int Process::getExecutionTime()
{
    int execTime = CPUExecutionTime;
    if ( IODeviceDelay != 0 )
        execTime += IODeviceOccupy;
    return execTime;
}

STATE Process :: getState()
{
    return state;
}

int Process :: nextState()
{
    switch (state) {
      case CP:
        if ( IODeviceDelay != 0 ) {
            state = IO;
            return IODeviceDelay;
        } else {
            state = FP;
            return CPUExecutionTime;
        }
      case IO:
        state = RC;
        return IODeviceOccupy;
      case RC:
        state = FP;
        return CPUExecutionTime - IODeviceDelay;
      default:
        return 0;
    }
}

void Process :: getFullInfo(int delay)
{
    cout << "Process with address " << this << " is scheduled. (delay:" << delay << ")" << endl
         << "CPU execution time: " << CPUExecutionTime << endl
         << "IO device id: " << IODeviceID << endl
         << "IO device delay: " << IODeviceDelay << endl
         << "IO device occupy: " << IODeviceOccupy << endl;
}

void Process :: getInfo(int delay)
{
    cout << "Process with address " << this << " is scheduled. (delay:" << delay << ")" << endl;
}
