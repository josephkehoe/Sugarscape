//
// Created by joseph on 03/03/16.
//

#include "NewSweepStrategy.h"

/**
 * Constructor - Little to do - base class constructor does all work
 * @param theWorld :Pointer to World Object
 * @see RndAsyncStrategy Constructor
 * @exception none
 */
NewSweepStrategy::NewSweepStrategy(World *sim) : RndAsyncStrategy(sim) {
//nothing to do
}

/**
 * run - Applies action to every location in lattice within parameter limits.
 * Calls shuffle before running -  each step has its own random ordering.
 * Then just call base class version
 * @param startX :Starting X position of tile we are executing
 * @param startY :starting Y position of tile
 * @param size :dimensions of our tile (we assume square tiles)
 * @param rule :The action we are running
 * @see RndAsyncStrategy Algorithm
 * @return true
 * @exception none
 *
 * For breakdown of algorithm see paper
 */
bool NewSweepStrategy::run(int startX, int startY, int size,Action *rule){
    shuffle();
    RndAsyncStrategy::run(startX,startY,size,rule);
}


