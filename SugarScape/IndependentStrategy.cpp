//
//  IndependentStrategy.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#include "IndependentStrategy.h"

IndependentStrategy::IndependentStrategy(World* theWorld):Strategy(theWorld){
    
}
IndependentStrategy::~IndependentStrategy(void){
    
}


/**
 * Performs action on entire lattice
 * @see Strategy
 * @return number of actions performed
 * @exception none
 */
bool IndependentStrategy::run(int startX, int startY, int size,Action* rule){
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
 * Performs action on entire lattice concurrently
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentStrategy::concurrentRun(Action* rule){
    int size=sim->getSize();
    return run(0,0,size,rule);
}


