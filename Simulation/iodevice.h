#ifndef IODEVICE_H
#define IODEVICE_H

#include <vector>
#include <map>

#include "simprocess.h"

class IODevice
{
  public:
    IODevice();
    ~IODevice();

    void assignProcess( Process *pPtr );
    void removeProcess();
    Process* getCurrentProcess();
    bool isBusy();

  private:
    bool IOBusy;
    Process* cPtr; // current process pointer
};

#endif // IODEVICE_H
