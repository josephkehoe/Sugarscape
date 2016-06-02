//
// Created by joseph on 03/03/16.
//

#ifndef SUGARSCAPE_NEWSWEEPSTRATEGY_H
#define SUGARSCAPE_NEWSWEEPSTRATEGY_H


#include "RndAsyncStrategy.h"

/*!  \class  RndAsyncStrategy
 \brief Asynchronous updating in random order

This assumes a random ordering is chosen for every step.
 That is, each step uses new random ordering.
 */
class NewSweepStrategy : public RndAsyncStrategy{

public:
    NewSweepStrategy(World *sim);
    virtual bool run(int, int , int ,Action*);
};


#endif //SUGARSCAPE_NEWSWEEPSTRATEGY_H
