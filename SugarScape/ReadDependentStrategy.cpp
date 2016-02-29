//
//  ReadAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#include "ReadDependentStrategy.h"

ReadDependentStrategy::ReadDependentStrategy(World* theWorld):Strategy(theWorld){
    
}
ReadDependentStrategy::~ReadDependentStrategy(void){
    
}


/**
 * Performs a read only action across entire lattice sequentially
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadDependentStrategy::run(int startX, int startY, int size,Action* rule){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();
    //Perform action
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        rule->executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
    }
    return true;
}

/**
 * Performs a read only action across entire lattice concurrently
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadDependentStrategy::concurrentRun(Action* rule){
    int size=sim->getSize();
    return run(0,0,size,rule);
}

