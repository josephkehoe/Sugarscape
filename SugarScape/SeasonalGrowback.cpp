//
//  SeasonalGrowback.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 11/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "SeasonalGrowback.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
SeasonalGrowback::SeasonalGrowback(World *sim, Strategy *theStrategy):IndependentAction(sim,theStrategy){
    
}

/**
 * Seasonal Growback Rule - Growback with winter and summer growing rates
 * @param place :location we are running rule on
 * @param group - not required for this rule
 * @see Seasonal Growback Rule
 * @return true
 * @exception none
 */
bool SeasonalGrowback::executeAction(Location * place, group *){
    if ((sim->getStep()/sim->getSeasonLength())%2==0) {//summer top half
        if (place->getX()*2<sim->getSize()) {
            place->setSugar(place->getSugar()+sim->getSugarGrowth());
        } else {
            place->setSugar(place->getSugar()+(sim->getSugarGrowth()/sim->getWinterRate()));
        }
    } else {//winter top half
        if (place->getX()*2<sim->getSize()) {
            place->setSugar(place->getSugar()+(sim->getSugarGrowth()/sim->getWinterRate()));
        } else {
            place->setSugar(place->getSugar()+sim->getSugarGrowth());
        }
    }
    return true;
    
}


