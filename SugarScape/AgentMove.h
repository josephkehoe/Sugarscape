//
//  AgentMove.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentMove__
#define __SugarScape__AgentMove__

#include <iostream>
#include "AgentBasicMove.h"



/*!  \class  AgentMove
 \brief Basic Move Defined in Sugarscape
 
Movement - M

 - Look out as far as vision permits in each of the four lattice directions, north, south, east and west;
 - Considering only unoccupied lattice positions, find the nearest position producing maximum welfare;
 - Move to the new position
 - Collect all resources at that location

 TYPE:   *Write Dependent*
 */
class AgentMove :public AgentBasicMove{
public:
    AgentMove(World *,Strategy*);
    virtual int pickIndex(std::vector<Location*>);
    virtual group* formGroup(Location *);
};

#endif /* defined(__SugarScape__AgentMove__) */
