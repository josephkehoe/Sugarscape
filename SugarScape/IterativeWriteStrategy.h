//
// Created by joseph on 30/05/16.
//

#ifndef SUGARSCAPE_ITERATIVEWRITESTRATEGY_H
#define SUGARSCAPE_ITERATIVEWRITESTRATEGY_H


#include "WriteStrategy.h"
/*!  \class  IterativeWriteStrategy Synchronous Write-Dependent iterated Actions must use this
 \brief Contains algorithm for executing Iterative Write-Dependent actions *synchronously*

Reproduction is an example of this type of action. It is write dependent and the action is applied to every neighbour
 in a single step.
 */
class IterativeWriteStrategy :public WriteStrategy{
public:
    IterativeWriteStrategy(World*);
    virtual ~IterativeWriteStrategy();
    virtual bool run(int,int,int,Action*);
    virtual bool concurrentRun(Action*);
};


#endif //SUGARSCAPE_ITERATIVEWRITESTRATEGY_H
