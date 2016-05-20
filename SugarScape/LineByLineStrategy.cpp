//
// Created by joseph on 01/03/16.
//

#include "LineByLineStrategy.h"

LineByLineStrategy::LineByLineStrategy(World *sim):Strategy(sim){
    //our work is done
}


bool LineByLineStrategy::run(int startX, int startY, int size,Action *rule) {
    Location *Lattice = sim->getLattice();
    int dim = sim->getSize();
    Location * loc=nullptr;
    Agent *resident=nullptr;
    group *grp=nullptr;
    //Perform action
#pragma omp parallel for
    for (int i = 0; i < size * size; ++i) {
        loc=&Lattice[(startX + i / size) * dim + startY + i % size];
        grp = rule->formGroup(loc);//get this group
        rule->executeAction(loc, grp);//execute action on this group
        //sync this group
        loc->sync();
        resident = loc->getAgent();
        if (resident != nullptr) resident->sync();
        if (grp != nullptr) {//sync everyone in the group
            for (int k = 0; k < grp->getSize(); ++k) {
                grp->getMembers()[k]->sync();//sync location
                resident=grp->getMembers()[k]->getAgent();
                if (nullptr != resident) resident->sync();//sync any agent at location
            }
            //delete group
            delete grp;
        }//grp handling
    }//parallel for
    return true;
}

bool LineByLineStrategy::concurrentRun(Action *rule){
    return run(0,0,sim->getSize(),rule);
}