//
// Created by joseph on 24/08/16.
//

#ifndef SUGARSCAPE_AGENTMOVESTRONGEST_H
#define SUGARSCAPE_AGENTMOVESTRONGEST_H

#include "AgentBasicMove.h"

/*!  \class  AgentMoveClosest
 \brief Basic Move Defined in Sugarscape with added Collision Resolution

Movement - M

 - Look out as far as vision permits in each of the four lattice directions, north, south, east and west;
 - Considering only unoccupied lattice positions, find the nearest position producing maximum welfare;
 - Move to the new position
 - Collect all resources at that location
 - In case two agents try move to the same location the strongest agent wins
 TYPE:   *Write Dependent*
 */

class AgentMoveStrongest :AgentBasicMove {
public:
    AgentMoveStrongest(World *sim, Strategy *theStrategy):AgentBasicMove(sim,theStrategy) {

    }

    virtual int pickIndex(std::vector<Location*>);
    virtual group* formGroup(Location *);
};


#endif //SUGARSCAPE_AGENTMOVESTRONGEST_H
