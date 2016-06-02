//
//  Diffusion.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Diffusion.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
Diffusion::Diffusion(World *sim, Strategy *theStrategy):Action(sim,theStrategy){//ReadAction
    //EMPTY
}

/**
 * If the correct number of steps have elapsed calculate diffusion.
 * New pollution is average of four von Neumann neighbours pollution level
 * @param loc :the location we are executing rule on
 * @param group - not used
 * @see Pollution Diffusion Rule
 * @return true if pollution was diffused
 * @exception none
 */
bool Diffusion::executeAction(Location *loc, group *){
    int size=sim->getSize();
    if (sim->getStep() % sim->getPollutionRate()==0) {
        Location* lattice=sim->getLattice();
        int diffusedPollution= lattice[sim->wrap(loc->getX()+1)*size+loc->getY()].getPollution()
                            +lattice[sim->wrap(loc->getX()-1)*size+loc->getY()].getPollution()
                            +lattice[loc->getX()*size+sim->wrap (loc->getY()+1)].getPollution()
                            +lattice[loc->getX()*size+sim->wrap(loc->getY()-1)].getPollution();
        loc->setPollution(diffusedPollution/4);
        return true;
    }else{
        return false;
    }
    
}

