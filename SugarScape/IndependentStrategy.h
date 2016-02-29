//
//  IndependentAction.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__IndependentStrategy__
#define __SugarScape__IndependentStrategy__

#include <iostream>
#include "Strategy.h"

/*!  \class  IndependentStrategy
 \brief Actions that require no interaction between agents
 
 The simplest possible agent actions.  No interaction between agents. Every agent acts independently.
 */
class IndependentStrategy:public Strategy{
public:
    IndependentStrategy(World*);
    virtual ~IndependentStrategy();
    virtual bool run(int,int,int,Action*);
    virtual bool concurrentRun(Action*);
};
#endif /* defined(__SugarScape__IndependentStrategy__) */
