#include "cpucoresupervisor.h"

CPUCoreSupervisor ::  CPUCoreSupervisor(int CPUCount)
{
    for ( int i = 0; i < CPUCount; i++ )
        cpus.push_back( CPUCore() );
}

CPUCoreSupervisor :: ~CPUCoreSupervisor()
{

}

void CPUCoreSupervisor :: assignProcess(multimap<int, Process*> &queue, Process *pPtr, int currentTime )
{
    for ( size_t i = 0; i < cpus.size(); i++ )
    {
        if ( !cpus.at(i).isBusy() )
        {
            cpus.at(i).assignProcess( pPtr, currentTime );
            queue.insert( pair<int, Process*>( currentTime + pPtr->nextState(), pPtr ) );
            break;
        }
    }
}

void CPUCoreSupervisor :: removeProcess( Process *pPtr )
{
    for ( size_t i = 0; i < cpus.size(); i++ )
        if ( cpus.at(i).getCurrentProcess() == pPtr )
            cpus.at(i).removeProcess();
}

int CPUCoreSupervisor :: getFreeSlots()
{
    int count = 0;
    for ( size_t i = 0; i < cpus.size(); i++ )
        if ( !cpus.at(i).isBusy() )
            count++;
    return count;

}

string CPUCoreSupervisor :: getUtilizationInfo( int elapsedTime )
{
    vector<CPUCore>::iterator it;
    string info;
    int id = 1;
    int utilizationTime;
    for ( it = cpus.begin(); it != cpus.end(); it++ )
    {
        utilizationTime = (*it).getUtilizationTime(elapsedTime);
        info.append( "cpu " + to_string(id++) + ": " + to_string( static_cast<double>( utilizationTime ) / elapsedTime * 100 ) + "%\n" );
    }
    return info;
}

void CPUCoreSupervisor :: clean()
{
    vector<CPUCore>::iterator it;
    for ( it = cpus.begin(); it != cpus.end(); it++ )
        if ( it->isBusy() )
            delete it->getCurrentProcess();
}
