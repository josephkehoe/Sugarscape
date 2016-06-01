//
// Created by joseph on 30/05/16.
//

#include "IterativeWriteStrategy.h"



/**
 * Construtor - pass World Pointer back to base class constructor
 * @param sim :Pointer to World Object
 * @exception none
 */
IterativeWriteStrategy::IterativeWriteStrategy(World *sim)
        :WriteStrategy(sim)
{
    //our work is done
}

/**
 * Destructor - Nothing to do
 * @exception none
 */
IterativeWriteStrategy::~IterativeWriteStrategy(){
    //NOTHING TO DO
}

/**
 * run action iteratively.  Call run until we have performed action on all possible neighbours
 * @param startX :X-coordinate of top left corner of grid we are running on
 * @param startY :Y-coordinate of top left corner of grid we are working on
 * @param size :Dimensions of grid
 * @param rule :Action of type *write dependent*
 * @return true
 * @exception none
 */
bool IterativeWriteStrategy::run(int startX, int startY, int size, Action* rule)
{
    int participants=rule->participantCount(startX, startY, size);
    while (participants>0) {
        WriteStrategy::run(startX, startY, size,rule);
        sim->sync();/*!< *MUST* sync before iterating */
        participants=rule->participantCount(startX, startY, size);
    }
    //sim->resetNeighbours();
    return true;
}


/**
 * Concurrent version of run. Tiled algorithm from base class but called iteratively
 * @return true
 * @exception none
 */
bool IterativeWriteStrategy::concurrentRun(Action* rule)
{
    int participants=rule->participantCount(0, 0, sim->getSize());
    while (participants>0) {
        WriteStrategy::concurrentRun(rule);
        sim->sync();/*!< *MUST* sync before iterating */
        participants=rule->participantCount(0, 0, sim->getSize());
    }
    //sim->resetNeighbours();
    return true;

}

