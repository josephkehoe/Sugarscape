//
// Created by joseph on 03/03/16.
//

#include "RndAsyncStrategy.h"


RndAsyncStrategy::RndAsyncStrategy(World *sim) : Strategy(sim){
    //initialise ordering array
    size=sim->getSize()*sim->getSize();
    ordering = new int[size];
    for(int i=0;i<size;++i){
        ordering[i]=i;
    }
    shuffle();//randomise ordering
}


bool RndAsyncStrategy::shuffle() {
    for(int i=0; i<size; ++i){
        int k=sim->getRnd(0,size);
        int temp=ordering[k];
        ordering[k]=ordering[i];
        ordering[i]=temp;
    }
    return true;
}

bool RndAsyncStrategy::run(int startX, int startY, int size,Action *rule) {
    Location *Lattice = sim->getLattice();
    int dim = sim->getSize();
    Location * loc=nullptr;
    Agent *resident=nullptr;
    group *grp=nullptr;
    //Perform action
#pragma omp parallel for
    for (int i = 0; i < size * size; ++i) {
        loc=&Lattice[(startX + ordering[i] / size) * dim + startY + ordering[i] % size];
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

bool RndAsyncStrategy::concurrentRun(Action *rule){
    return run(0,0,sim->getSize(),rule);
}

RndAsyncStrategy::~RndAsyncStrategy() {
    delete [] ordering;
}
