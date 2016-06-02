//
//  IndependentStrategy.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__IndependentStrategy__
#define __SugarScape__IndependentStrategy__

#include <iostream>
#include "Action.h"
#include "Strategy.h"

/*!  \class  IndependentAction
 \brief Synchronous updating where agents require no interaction 
 
 The simplest possible agent actions.  No interaction between agents. Every agent acts independently.
 */
class IndependentStrategy:public Strategy{
public:
    IndependentStrategy(World*);
    virtual ~IndependentStrategy();
    virtual bool run(int,int,int,Action*);
};
#endif /* defined(__SugarScape__IndependentStrategy__) */
