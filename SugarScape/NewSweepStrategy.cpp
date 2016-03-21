//
// Created by joseph on 03/03/16.
//

#include "NewSweepStrategy.h"

NewSweepStrategy::NewSweepStrategy(World *sim) : RndAsyncStrategy(sim) {
//nothing to do
}


bool NewSweepStrategy::run(int startX, int startY, int size,Action *rule){
    shuffle();
    RndAsyncStrategy::run(startX,startY,size,rule);
}
bool NewSweepStrategy::concurrentRun(Action*){
    return run(0,0,sim->getSize(),rule);
}