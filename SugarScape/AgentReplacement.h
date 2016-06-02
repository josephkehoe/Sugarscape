//
//  AgentReplacement.h
//  SugarScape
//
//  Created by Joseph kehoe on 07/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentReplacement__
#define __SugarScape__AgentReplacement__

#include <iostream>
#include "WriteAction.h"

/*!  \class  AgentReplacement
 \brief Replacement Rule
 
 Replacement - R_[a,b]
 When an agent dies it is replaced by an agent of age 0 having random genetic attributes, random position on the Sugarscape, random initial endowment, and a maximum age selected from the range [a,b].

TYPE:   *Write Dependent*
 */
class AgentReplacement :public Action{//WriteAction
    std::vector<Location* > freeSlots;
    unsigned long  populateFreeSlots(void);
public:
    AgentReplacement(World *, Strategy*);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    
};
#endif /* defined(__SugarScape__AgentReplacement__) */
