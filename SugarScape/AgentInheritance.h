//
//  AgentInheritance.h
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Inheritance__
#define __SugarScape__Inheritance__

#include <iostream>
#include "ReadAction.h"


/*!  \class  AgentInheritance
 \brief Implements the AgentInheritance Rule
 
 Agent AgentInheritance $I$
 When an agent dies its wealth is equally distributed among all its living children.

 TYPE:   *Read Dependent*
 */

class AgentInheritance:public Action{//ReadAction
public:
    AgentInheritance(World *,Strategy*);
    virtual bool executeAction(Location *, group *);

};

#endif /* defined(__SugarScape__Inheritance__) */
