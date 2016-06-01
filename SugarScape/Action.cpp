//
//  Action.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Action.h"


Action::Action(World* theWorld):sim(theWorld){
    
}
Action::~Action(void){
    
}
/**
 * Sequentially performs action on square section of Lattice
 * @param startX :start row on lattice
 * @param startY :start column on lattice
 * @param size :dimension of lattice (assume square lattice)
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Action::run(int startX,int startY, int size){
    return false;
}
/**
 * Concurrently performs action on entire Lattice
 * @return true if ok, false to indicate error
 * @exception none
 */
bool Action::concurrentRun(void){
    return false;
}


/**
 Calculate the number of active participants in this action on the grid
 Default is number of agents - assume they are all active
 @param startX :start Index for row
 @param startY :start index for column
 @param dimSize :Dimensions of grid size
 @returns number of agents in this grid
 @exception none
 */
int Action::participantCount(int startX, int startY, int dimSize)
{
    int pcount=0;
#pragma omp parallel for
    for (int i=startX; i<startX+dimSize; ++i) {
        for (int k=startY; k<startY+dimSize; ++k) {
            if (sim->getAgent(std::pair<int,int>(i, k)) != nullptr && sim->getAgent(std::pair<int,int>(i, k))->isDone()==false) {
                ++pcount;
            }
        }
    }
    return pcount;
}


/**
 pick index from list of available locations

 Picks randomly, May be required to help form group reimplement if you want
 a more intelligent picking behaviour e.g. pick best/nearest/weakest neighbour

 @param possibleDestinations :vector of locations we can move to
 @returns index of chosen location in vector
 @exception none
 */
int Action::pickIndex(std::vector<Location*> possibleDestinations)
{
    return sim->getRnd(0,(int)possibleDestinations.size()-1);//pick random location
}