//
//  WriteAction.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__WriteStrategy__
#define __SugarScape__WriteStrategy__

#include <iostream>
#include "Strategy.h"

/*!  \class  WriteStrategy All Write-Dependent Actions use this
 \brief Contains algorithm for executing synchronous  Write-Dependent actions
 
 
 */
class WriteStrategy:public Strategy{
public:
    WriteStrategy(World*);
    virtual ~WriteStrategy();
    virtual bool run(int,int,int,Action*);
    virtual bool concurrentRun(Action*);
    virtual int participantCount(int,int,int);
    virtual int pickIndex(std::vector<Location*>);
};
#endif /* defined(__SugarScape__WriteStrategy__) */
