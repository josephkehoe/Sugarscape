//
// Created by joseph on 24/08/16.
//

#include "UniformChoice.h"

/**
 * Constructor - Create random ordering of locations
 * @param theWorld :Pointer to World Object
 * @see Strategy Constructor
 * @exception none
 */
UniformChoice::UniformChoice(World *sim) : Strategy(sim){
    //initialise ordering array
    size=sim->getSize()*sim->getSize();/*!< size is dimension squared *///
    ordering = new int[size];
    for(int i=0;i<size;++i){
        ordering[i]=i;
    }
    shuffle();//randomise ordering
}

/**
 * Destructor - delete ordering array
 * @exception none
 */
UniformChoice::~UniformChoice() {
    delete [] ordering;
}

/**
 * Shuffle - Create random ordering of locations
 *
 * Just iterate through array putting random locations in the array!
 * Need to work on this to ensure the correct number of agents are picked
 * @return true - placeholder return value for now
 * @see Strategy Constructor
 * @exception none
 */
bool UniformChoice::shuffle() {
    int k=0;
    for(int i=0; i<size; ++i){
        k=sim->getRnd(0,size);
        ordering[i]=k;
    }
    return true;
}

/**
 * run - Applies action to every location in lattice within parameter limits.
 * Slightly complicated by dual state of framework (we must sync after each individual update)
 * @param startX :Starting X position of tile we are executing
 * @param startY :starting Y position of tile
 * @param size :dimensions of our tile (we assume square tiles)
 * @param rule :The action we are running
 * @return true
 * @exception none
 */
bool UniformChoice::run(int startX, int startY, int size,Action *rule) {
    Location *Lattice = sim->getLattice();
    int dim = sim->getSize();
    Location * loc=nullptr;
    Agent *resident=nullptr;
    group *grp=nullptr;
    //Perform action
    for (int i = 0; i < size * size; ++i) {
        loc = &Lattice[(startX + ordering[i] / size) * dim + startY + ordering[i] % size];
        grp = rule->formGroup(loc);/*!< get this group */
        if (grp != nullptr) {/*!< If there is work to do then do it */
            rule->executeAction(loc, grp);/*!< execute action on this group */
            std::pair<int, int> thePos;
            thePos = loc->getPosition();
            int v = sim->getMaxVision();
            loc = nullptr;
            for (int j = thePos.first - v; j <= thePos.first + v; ++j) {
                loc = sim->getLocation(std::pair<int, int>(j, thePos.second));
                loc->sync();
                if (loc->hasAgent())
                    loc->getAgent()->sync();
            }
            for (int k = thePos.second - v; k <= thePos.second + v; ++k) {
                loc = sim->getLocation(std::pair<int, int>(thePos.first, k));
                loc->sync();
                if (loc->hasAgent()) loc->getAgent()->sync();
            }
        }
    }
    return true;
}

/**
 * returns true if we need to sync the world after strategy is applied
 * Asynch does *not*!
 * @return false as synchronisation is *not* required
 * @exception none
 */
bool UniformChoice::needsSync(void){
    return false;
}