//
// Created by joseph on 03/03/16.
//

#ifndef SUGARSCAPE_NEWSWEEPSTRATEGY_H
#define SUGARSCAPE_NEWSWEEPSTRATEGY_H


#include "RndAsyncStrategy.h"

class NewSweepStrategy : public RndAsyncStrategy{

public:
    NewSweepStrategy(World *sim1, World *sim);
    virtual bool run(int, int , int ,Action*);
    virtual bool concurrentRun(Action*);
};


#endif //SUGARSCAPE_NEWSWEEPSTRATEGY_H
