//
// Created by joseph on 01/03/16.
//

#ifndef SUGARSCAPE_LINEBYLINESTRATEGY_H
#define SUGARSCAPE_LINEBYLINESTRATEGY_H

#include "Strategy.h"

class LineByLineStrategy :public Strategy{

public:
    LineByLineStrategy(World*);
    virtual bool run(int, int , int ,Action*);
    virtual bool concurrentRun(Action*);
};


#endif //SUGARSCAPE_LINEBYLINESTRATEGY_H
