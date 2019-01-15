#include "iodevice.h"

IODevice ::  IODevice()
{
    cPtr = nullptr;
    IOBusy = false;
}

IODevice :: ~IODevice()
{

}

void IODevice :: assignProcess( Process *pPtr )
{
    IOBusy = true;
    cPtr = pPtr;
    cout << pPtr << " is assigned to IO device" << endl;
}

void IODevice :: removeProcess()
{
    IOBusy = false;
    cPtr = nullptr;
}

Process* IODevice :: getCurrentProcess()
{
    return cPtr;
}

bool IODevice :: isBusy()
{
    return IOBusy;
}
