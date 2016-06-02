//
//  Strategy.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#include "Strategy.h"

/**
 * Constructor - Little to do - Initialise sim pointer
 * @param theWorld :Pointer to World Object
 * @exception none
 */
Strategy::Strategy(World* theWorld):sim(theWorld){
    
}

/**
 * Destructor - Nothing to do
 * @exception none
 */
Strategy::~Strategy(void){
    
}
/**
 * Performs action on square section of Lattice
 * @param startX :start row on lattice
 * @param startY :start column on lattice
 * @param size   :dimension of lattice (assume square lattice)
 * @param rule   :The action we are applying to each agent
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Strategy::run(int startX,int startY, int size,Action*){
    return false;
}
/**
 * Concurrently performs action on entire Lattice. Base case is if no tiling algorithm exists
 * then we just call normal run as it also handles concurrency.
 * @param rule   :The action we are applying to each agent
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Strategy::concurrentRun(Action* rule){
    return run(0,0,sim->getSize(),rule);
}

/**
 * returns true if we need to sync the world after strategy is applied
 * Assumes we do.  change to false for async strategies
 * @return true if synchronisation is required
 * @exception none
 */
bool Strategy::needsSync(void){
    return true;
}
