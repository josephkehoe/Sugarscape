//
//  IndependentAction.cpp
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
 * Performs action on entire lattice synchronously (For independent actions this is the same
 * *asynchronously* and *synchronously*)
 * @param startX :start row on lattice
 * @param startY :start column on lattice
 * @param size   :dimension of lattice (assume square lattice)
 * @param rule   :The action we are applying to each agent
 * @return true if ok, false to indicate error
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentStrategy::run(int startX, int startY, int size, Action *Rule){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();
    //Perform action
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        Rule->executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
    }
    return true;
}




