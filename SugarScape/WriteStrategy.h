//
//  WriteAction.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__WriteStrategy__
#define __SugarScape__WriteStrategy__

#include <iostream>
#include "Strategy.h"

/*!  \class  WriteStrategy
 \brief All synchronous Write-Dependent Actions must use this
 
Contains algorithm for executing Write-Dependent actions synchronously.
 Most complex of interaction type.
 */
class WriteStrategy:public Strategy{
public:
    WriteStrategy(World*);
    virtual ~WriteStrategy();
    virtual bool run(int,int,int,Action*);
    virtual bool concurrentRun(Action*);
};
#endif /* defined(__SugarScape__WriteStrategy__) */
