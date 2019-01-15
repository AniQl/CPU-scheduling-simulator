#include "iodevicesupervisor.h"

IODeviceSupervisor ::  IODeviceSupervisor(int IODCount )
{
    for ( int i = 0; i < IODCount; i++ )
        iod.push_back( IODevice() );
}

IODeviceSupervisor :: ~IODeviceSupervisor()
{

}

void IODeviceSupervisor :: assignProcess( multimap<int, Process*> &queue, Process *pPtr, int currentTime )
{
    size_t pos = static_cast<size_t>( pPtr->getIOID() );
    if ( !iod.at(pos).isBusy() )
    {
        iod.at(pos).assignProcess( pPtr );
        queue.insert( pair<int, Process*>( currentTime + pPtr->nextState(), pPtr ) );
    }
}

void IODeviceSupervisor :: removeProcess( Process *pPtr )
{
    for ( size_t i = 0; i < iod.size(); i++ )
        if ( iod.at(i).getCurrentProcess() == pPtr )
            iod.at(i).removeProcess();
}

int IODeviceSupervisor :: getFreeSlots(size_t IOID)
{
    return !iod.at(IOID).isBusy();
}

void IODeviceSupervisor :: clean()
{
    vector<IODevice>::iterator it;
    for ( it = iod.begin(); it != iod.end(); it++ )
        if ( it->isBusy() )
            delete it->getCurrentProcess();

}
