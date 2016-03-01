//
// Created by joseph on 01/03/16.
//

#include "LineByLineStrategy.h"


LineByLineStrategy::LineByLineStrategy(World *sim):Strategy(sim){
    //our work is done
}


bool LineByLineStrategy::run(int startX, int startY, int size,Action *rule){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();
    //Perform action
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        rule->executeAction(&Lattice[(startX+i/size)*dim+startY+i%size],nullptr);
        //SYNC EACH AGENT IN TURN
        Lattice[(startX+i/size)*dim+startY+i%size].sync();
        Agent * resident=Lattice[(startX+i/size)*dim+startY+i%size].getAgent();
        if (resident!= nullptr) resident->sync();
    }
    return true;
}

bool LineByLineStrategy::concurrentRun(Action *rule){
    return run(0,0,sim->getSize(),rule);
}