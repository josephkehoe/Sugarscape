//
//  IndependentAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "IndependentAction.h"
#include "Strategy.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param theWorld :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
IndependentAction::IndependentAction(World* theWorld, Strategy *theStrategy):Action(theWorld,theStrategy){
    
}
IndependentAction::~IndependentAction(void){
    
}


/**
 * Performs action on entire lattice
 * @see Action
 * @return number of actions performed
 * @exception none
 */
//bool IndependentAction::run(int startX, int startY, int size){
//    theStrategy->run(startX,startY,size,this);
////    Location* Lattice=sim->getLattice();
////    int dim=sim->getSize();
////    //Perform action
////#pragma omp parallel for
////    for (int i=0; i<size*size; ++i) {
////        executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
////    }
////    return true;
//
//}
/**
 * Performs action on entire lattice concurrently
 * @see Action
 * @return number of actions performed
 * @exception none
 */
//bool IndependentAction::concurrentRun(void){
//    int size=sim->getSize();
//    return theStrategy->run(0,0,size,this);//run(0,0,size);
//}


