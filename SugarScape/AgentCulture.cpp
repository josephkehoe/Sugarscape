//
//  AgentCulture.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentCulture.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentCulture::AgentCulture(World *sim,Strategy* theStrategy):ReadAction(sim,theStrategy){
    //EMPTY
}

/**
 * If location contains an agent then apply culture rule to that agent
 * @param loc :location to be checked
 * @see Culture Rule
 * @return true if location contained agent else false
 * @exception none
 */
bool AgentCulture::executeAction(Location *loc, group* ){
    if (loc->hasAgent()) {
        std::vector<Agent*> neighbours=sim->getNeighbours(loc->getPosition(), 1);
        for(auto a:neighbours){
            std::vector<bool> tags=a->getCulture();
            int index=sim->getRnd(0, sim->getCultureCount()-1);
            loc->getAgent()->setTag(index,tags[index]);

        }
        return true;
    }else{
        return false;
    }
}

