#ifndef IODEVICESUPERVISOR_H
#define IODEVICESUPERVISOR_H

#include "iodevice.h"

class IODeviceSupervisor
{
  public:
    IODeviceSupervisor( int IODCount );
    ~IODeviceSupervisor();

    void assignProcess( multimap<int, Process*> &queue, Process *pPtr, int currentTime );
    void removeProcess( Process *pPtr );
    int  getFreeSlots( size_t IOID );
    void clean();

  private:
    vector<IODevice> iod;
};

#endif // IODEVICESUPERVISOR_H
