//
//  ReadDependentStrategy.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__ReadDependentStrategy__
#define __SugarScape__ReadDependentStrategy__

#include <iostream>
#include "Strategy.h"

/*!  \class  ReadDependentStrategy
 \brief Synchronous updates where the agent reads the neighbour's state but only update their own
 
 Read-Dependent Rules with synchronous updating all use this.
 */
class ReadDependentStrategy:public Strategy{
public:
    ReadDependentStrategy(World*);
    virtual ~ReadDependentStrategy();
    virtual bool run(int,int,int,Action*);
//    virtual bool concurrentRun(Action*);USE INHERITED VERSION
};
#endif /* defined(__SugarScape__ReadDependentStrategy__) */
