//
//  AgentMetabolism.cpp
//  SScapeGUI
//
//  Created by Joseph kehoe on 26/08/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
//

#include "AgentMetabolism.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentMetabolism::AgentMetabolism(World *sim,Strategy *theStrategy):Action(sim,theStrategy){//IndependentAction                                                                                                             theStrategy){
    
}

/**
 * Decrements an agents sugar by their metabolism
 * @param loc :Location in lattice we are running action on
 * @param group pointer not used - nullptr passed in
 * @see Metabolism in book
 * @return true if agent was at location else false
 * @exception none
 */
bool AgentMetabolism::executeAction(Location * loc, group * ){
    if (loc->hasAgent()) {
        Agent *agent =loc->getAgent();
        agent->incSugar(-agent->getMetabolism());
        agent->incAge();
    }
    return true;
}


