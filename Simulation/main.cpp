#include <time.h>
#include <math.h>

#include "cpucoresupervisor.h"
#include "iodevicesupervisor.h"

static int CPUCount = 4;
static int IODCount = 5;
static double lambda = 0.65;

void signalCPUQueue( int simTime, CPUCoreSupervisor &cpuCS, multimap<int, Process*> &FELQueue, vector<Process*> &CPUQueue);
void signalIOQueue(  int simTime, IODeviceSupervisor &ioDS, multimap<int, Process*> &FELQueue, vector<multimap<int, Process*>> &IOQueue);

int main() {
    unsigned int seed = static_cast<unsigned int>( time(nullptr) );
    seed = 1546833492; // manual seed
    cout << "Current seed: " << seed << endl;
    srand(seed);

    int turnaroundTime = 0; // total
    int executionTime = 0;  // total

    UniformGenerator *ug = new UniformGenerator(rand());
    ExpGenerator eg(lambda, ug);

    multimap<int, Process*> FELQueue;           // future event list main queue
    vector<Process*> CELCPUQueue;               // conditional event list CPU queue
    vector<multimap<int, Process*>> CELIOQueue; // conditional event list IO queue
    CELIOQueue.resize( static_cast<unsigned int>(IODCount) );
    CPUCoreSupervisor cpuCS(CPUCount);
    IODeviceSupervisor ioDS(IODCount);

    int prevSimTime, creationDelay, simulationLimit;
    int processCountTotal = 1, processCount = 0, simulationTime = 0;
    Process *pPtr, *newPtr;
    char continuous;

    cout << "Simulation time limit: ";
    cin >> simulationLimit;
    cout << "Is simulation continuous? "; // y for yes
    cin >> continuous;

    cout << endl << "Simulation time: " << simulationTime << endl;
    creationDelay = eg.Rand();
    newPtr = new Process(IODCount, simulationTime + creationDelay);
    FELQueue.insert( pair<int, Process*>( creationDelay, newPtr ) );
    if ( continuous != 'y' )
        newPtr->getFullInfo(creationDelay);
    else
        newPtr->getInfo(creationDelay);

    cin.ignore();
    while( true ) {
        if ( continuous != 'y' )
            cin.get();

        if ( !FELQueue.empty() ) { // FELqueue is not empty
            prevSimTime = simulationTime;
            simulationTime = FELQueue.begin()->first;
            if (simulationTime > simulationLimit)
                break;
            pPtr = FELQueue.begin()->second;
            FELQueue.erase( FELQueue.begin() );

            if (prevSimTime != simulationTime)
                cout << endl << "Simulation time: " << simulationTime << endl;

            if ( pPtr->getState() == CP ) {
                creationDelay = eg.Rand();
                newPtr = new Process(IODCount, simulationTime + creationDelay);
                FELQueue.insert( pair<int, Process*>( creationDelay + simulationTime, newPtr ) );
                processCountTotal++;
                if ( continuous != 'y' )
                    newPtr->getFullInfo(creationDelay);
                else
                    newPtr->getInfo(creationDelay);

                cout << pPtr << " assigned to CELCPUQueue" << endl;
                CELCPUQueue.push_back(pPtr); // assign process to CELCPUQueue to follow FIFO rules
                signalCPUQueue( simulationTime, cpuCS, FELQueue, CELCPUQueue );

            } else if ( pPtr->getState() == IO ) {
                cpuCS.removeProcess(pPtr); // remove process from cpu
                // assign process to CELIOQueue to follow SJF rules
                cout << pPtr << " assigned to CELIOQueue" << endl;
                CELIOQueue.at( static_cast<size_t>( pPtr->getIOID() ) ).insert(pair<int, Process*>(pPtr->getIOOccupy(), pPtr) );
                signalIOQueue( simulationTime, ioDS, FELQueue, CELIOQueue );    // signal io queue to request io device resources
                signalCPUQueue( simulationTime, cpuCS, FELQueue, CELCPUQueue ); // signal cpu queue to request cpu resources

            } else if ( pPtr->getState() == RC ) {
                ioDS.removeProcess(pPtr); // remove process from io device
                cout << pPtr << " assigned to CELCPUQueue" << endl;
                CELCPUQueue.push_back(pPtr); // assign process to CELCPUQueue to follow FIFO rules
                signalCPUQueue( simulationTime, cpuCS, FELQueue, CELCPUQueue ); // signal cpu queue to request cpu resources
                signalIOQueue( simulationTime, ioDS, FELQueue, CELIOQueue );    // signal io queue to request io device resources

            } else {
                cpuCS.removeProcess(pPtr); // remove process from cpu
                executionTime += pPtr->getExecutionTime();
                turnaroundTime += simulationTime - pPtr->getCreationTime();
                cout << pPtr << " finished in " << simulationTime - pPtr->getCreationTime() << "ms "
                    << "(ideal: " << pPtr->getExecutionTime() << "ms)" << endl;
                processCount++;
                delete pPtr;

                signalCPUQueue( simulationTime, cpuCS, FELQueue, CELCPUQueue ); // signal cpu queue to request cpu resources
            }
        }
        else { // CELqueue && FELqueue are empty, end simulation
            break;
        }
    }
    cout << endl << "Total processes vs finished processes: " << processCountTotal << ":" << processCount << endl;
    cout << endl << "CPU utilization information" << endl;
    cout << cpuCS.getUtilizationInfo(simulationLimit) << endl;
    cout << "Avarage processes per ms: ";
    cout << static_cast<double>(processCount)/simulationLimit << endl;
    cout << endl << "Avarage waiting time in queue: "
         << static_cast<double>(turnaroundTime - executionTime)/processCount << endl;

    // memory release
    cpuCS.clean();
    ioDS.clean();
	
    while ( !CELCPUQueue.empty() )
    {
        delete *CELCPUQueue.begin();
        CELCPUQueue.erase(CELCPUQueue.begin());
    }
    for ( size_t i = 0; static_cast<int>(i) < IODCount; i++ )
    {
        while ( !CELIOQueue.at(i).empty() )
        {
            delete CELIOQueue.at(i).begin()->second;
            CELIOQueue.at(i).erase(CELIOQueue.at(i).begin());
        }
    }

	cin >> seed;
}

void signalCPUQueue( int simTime, CPUCoreSupervisor &cpuCS, multimap<int, Process*> &FELQueue, vector<Process*> &CPUQueue) {
    // checking CELCPUQueue
    Process *pPtr;
    for ( int i = 0; i < cpuCS.getFreeSlots(); i++ ) { // CPUQueue is not empty and CPU can take the task
        if ( !CPUQueue.empty() ) {
            pPtr = *CPUQueue.begin();
            CPUQueue.erase( CPUQueue.begin() );
            cpuCS.assignProcess( FELQueue, pPtr, simTime );
        } else break;
    }
}

void signalIOQueue(  int simTime, IODeviceSupervisor &ioDS, multimap<int, Process*> &FELQueue, vector<multimap<int, Process*>> &IOQueue) {
    // checking CELIOQueue
    Process *pPtr;
    for ( size_t i = 0; i < static_cast<size_t>(IODCount); i++ ) {
        for ( int j = 0; j < ioDS.getFreeSlots(i); j++ ) {
            if ( !IOQueue.at(i).empty() ) {
                pPtr = IOQueue.at(i).begin()->second;
                IOQueue.at(i).erase( IOQueue.at(i).begin() );
                ioDS.assignProcess( FELQueue, pPtr, simTime );
            } else break;
        }
    }
}
