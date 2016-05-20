//
// Created by joseph on 03/03/16.
//

#ifndef SUGARSCAPE_RNDASYNCSTRATEGY_H
#define SUGARSCAPE_RNDASYNCSTRATEGY_H


#include <netinet/in.h>
#include "Strategy.h"

class RndAsyncStrategy : public Strategy{
    int *ordering;
    int size;
protected:
    bool shuffle();
public:
    RndAsyncStrategy(World *sim);

    virtual ~RndAsyncStrategy();
    virtual bool run(int, int , int ,Action*);
    virtual bool concurrentRun(Action*);
};

RndAsyncStrategy::RndAsyncStrategy(World *sim) : Strategy(sim) { }


#endif //SUGARSCAPE_RNDASYNCSTRATEGY_H
