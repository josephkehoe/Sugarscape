//
// Created by joseph on 24/08/16.
//

#ifndef SUGARSCAPE_AGENTMOVECLOSEST_H
#define SUGARSCAPE_AGENTMOVECLOSEST_H


#include "AgentBasicMove.h"

/*!  \class  AgentMoveClosest
 \brief Basic Move Defined in Sugarscape with added Collision Resolution

Movement - M

 - Look out as far as vision permits in each of the four lattice directions, north, south, east and west;
 - Considering only unoccupied lattice positions, find the nearest position producing maximum welfare;
 - Move to the new position
 - Collect all resources at that location
 - In case two agents try move to the same location the closest to the destination wins
 TYPE:   *Write Dependent*
 */
class AgentMoveClosest : public AgentBasicMove{
public:
    AgentMoveClosest(World *,Strategy*);
    virtual int pickIndex(std::vector<Location*>);
    virtual group* formGroup(Location *);
};


#endif //SUGARSCAPE_AGENTMOVECLOSEST_H
