//
// Created by joseph on 01/03/16.
//

#include "LineByLineStrategy.h"
#include "Action.h"
/**
 * Constructor - Little to do - base class constructor does all work
 * @param sim :Pointer to World Object
 * @see Strategy Constructor
 * @exception none
 */
LineByLineStrategy::LineByLineStrategy(World *sim):Strategy(sim){
    //our work is done
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
bool LineByLineStrategy::run(int startX, int startY, int size,Action *rule) {
    Location *Lattice = sim->getLattice();
    int dim = sim->getSize();
    Location * loc=nullptr;
    Agent *resident=nullptr;
    group *grp=nullptr;
    /*!<Perform action */
#pragma omp parallel for
    for (int i = 0; i < size * size; ++i) {
        loc=&Lattice[(startX + i / size) * dim + startY + i % size];
        grp = rule->formGroup(loc);/*!< get this group */
        rule->executeAction(loc, grp);/*!<execute action on this group */
        /*!< sync this group */
        loc->sync();
        resident = loc->getAgent();
        if (resident != nullptr) resident->sync();
        if (grp != nullptr) {/*!< sync this group sync everyone in the group */
            for (int k = 0; k < grp->getSize(); ++k) {
                grp->getMembers()[k]->sync();/*!< sync location */
                resident=grp->getMembers()[k]->getAgent();
                if (nullptr != resident) resident->sync();/*!< sync any agent at location */
            }
            /*!< delete group */
            delete grp;
        }//grp handling
    }//parallel for
    return true;
}


/**
 * returns true if we need to sync the world after strategy is applied
 * Asynch does *not*!
 * @return false as synchronisation is *not* required
 * @exception none
 */
bool LineByLineStrategy::needsSync(void){
    return false;
}