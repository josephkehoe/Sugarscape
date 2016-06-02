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
 Strategy class runs rules within a step in some defined way (synchronous, asynchronous, etc.)
 When a rule object is created we pass in a (derived) strategy to it.  It then employs this strategy to schedule rule
 application within a step.
 */

class Strategy{
protected:
    World *sim; /*!< The object containing the entire simulation */
public:
    Strategy(World*);
    virtual ~Strategy();
    virtual bool run(int,int,int,Action*); /*!< Standard run algorithm handling concurrency */
    virtual bool concurrentRun(Action*);   /*!< Tiled implementation for concurrency -if it exists */
    virtual bool needsSync(void); /*!< Do we need to sync world after strategy application? */
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

