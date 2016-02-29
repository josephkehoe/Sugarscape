//
//  Strategy.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Strategy.h"


Strategy::Strategy(World* theWorld):sim(theWorld){
    
}
Strategy::~Strategy(void){
    
}
/**
 * Sequentially performs action on square section of Lattice
 * @param startX :start row on lattice
 * @param startY :start column on lattice
 * @param size :dimension of lattice (assume square lattice)
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Strategy::run(int startX,int startY, int size,Action*){
    return false;
}
/**
 * Concurrently performs action on entire Lattice
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Strategy::concurrentRun(Action*){
    return false;
}


