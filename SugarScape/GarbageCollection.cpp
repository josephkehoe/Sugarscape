//
//  GarbageCollection.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 16/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "GarbageCollection.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
GarbageCollection::GarbageCollection(World *sim, Strategy *theStrategy)
    :IndependentAction(sim,theStrategy)
{
    //nothing to do here
}
/**
 * Deletes dead agent kept by location
 * @param loc :Location we are checking
 * @param Group we need - not required by this rule
 * @see Death, Replacement, Combat
 * @return true if there was a dead agent to remove else false
 * @exception none
 */
bool GarbageCollection::executeAction(Location * loc, group *)
{
    return loc->putOutGarbage();
}

