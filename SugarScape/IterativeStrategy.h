//
//  IterativeStrategy.h
//  SugarScape
//
//  Created by Joseph kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__IterativeStrategy__
#define __SugarScape__IterativeStrategy__

#include <iostream>
#include "WriteStrategy.h"

/*!  \class  IterativeWriteAction
 \brief Write-Dependent Actions that are iterative
 
 Base Class for all iterative Write-Dependent Actions If an action is applied to every (or more than one) neighbour each in turn during a single step then it inherits from this
 */
class IterativeStrategy:public WriteStrategy{ 

public:
    IterativeStrategy(World*);
    virtual bool run(int startX, int startY, int size,Action*);
    virtual bool concurrentRun(Action*);
    virtual int  participantCount(int, int, int);
};

#endif /* defined(__SugarScape__IterativeStrategy__) */
