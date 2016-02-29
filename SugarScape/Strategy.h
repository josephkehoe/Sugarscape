//
//  Strategy.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 29/02/2016.
//  Copyright (c) 2016 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Strategy__
#define __SugarScape__Strategy__

#include <iostream>
#include <algorithm>
#include "Location.h"
#include "group.h"
#include "World.h"
#include "Action.h"


/*!  \class  Strategy
 \brief Abstract base class for Strategies (sync, Async Updating)
 
 Derived actions need to define run and concurrentRun functions as they are pure virtual. 
 run and concurrentRun perform actions on lattice.
 */

class Strategy{
protected:
    World *sim; /*!< The object containing the entire simulation */
public:
    Strategy(World*);
    virtual ~Strategy();
    virtual bool run(int,int,int,Action*);
    virtual bool concurrentRun(Action*);
};
#endif /* defined(__SugarScape__Strategy__) */


//!
/*!
 <#detail#>
 */



/*!< <#description#> */


/**
 * <#description#>
 * @param <#param1#>
 * @param <#param2#>
 * @see <#ref#>
 * @return <#returnValue#>
 * @exception <#exceptionValue#>
 */


/*!  \class  <#name#>
 \brief <#brief#>
 
 <#description#>
 */

