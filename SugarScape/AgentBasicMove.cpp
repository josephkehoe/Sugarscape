//
//  AgentBasicMove.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 10/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentBasicMove.h"

/**
 * Constructor - passes world pointer to base class constructor
 * @param sim :Pointer to World Object
 * @param myStrategy :Pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentBasicMove::AgentBasicMove(World *sim, Strategy* myStrategy)
    :Action(sim,myStrategy)//WriteAction
{
    //our work is done
}



/**
 * Moves an agent to the location in the group object
 * Consumes sugar at new location
 * If location is empty then do nothing (this should not  occur!)
 * @param loc : Pointer to location we are acting on
 * @param grp : Pointer to group object containing destination
 * @see Move Rule
 * @return true if all ok
 * @exception none
 */
bool AgentBasicMove::executeAction(Location *loc, group * grp)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        std::pair<int,int> currPosition=theAgent->getPosition();
        std::pair<int,int> newPosition=grp->getMembers()[0]->getPosition();
        sim->setAgent(currPosition, nullptr);/*!< remove old location ptr to agent */
        theAgent->setPosition(newPosition);/*!< set new position to new location */
        sim->setAgent(newPosition,theAgent);/*!< add ptr to agent at new location */
        theAgent->incSugar(grp->getMembers()[0]->getSugar());/*!< eat sugar at new location */
        grp->getMembers()[0]->setSugar(0);/*!< sugar at new location now consumed */
        return true;
    }else{
        //std::cerr << "executed basicMove on location with no agent! " << std::endl;
        return false;/*!< no agent present so do nothing */
    }
}

/**
 * Pick a random empty location within our neighbourhood as defined by our vision
 * @param loc :Our location
 * @see Move Rule
 * @return Our chosen location held in a group object (or our existing location if we have no move
 * @exception none
 */
group* AgentBasicMove::formGroup(Location *loc)
{
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {/*!< Agent at this location */
        ourChoice = new group();     
        Agent* theAgent=loc->getAgent();
        std::vector<Location*> possibleDestinations=sim->getEmptyNeighbourhood(theAgent->getPosition(), theAgent->getVision());/*!< find all empty locations */
        if (possibleDestinations.size()!=0) {/*!< check to see if we can move anywhere */
            int index=pickIndex(possibleDestinations);
            ourChoice->push_back(possibleDestinations[index]);
            ourChoice->setRank(sim->getRnd(0,10));
            ourChoice->setPrimeMover(loc);
            ourChoice->setActiveParticipants(1);//one active participant per group - the agent moving
        }
        else{/*!< nowhere to move so stay here */
            ourChoice->push_back(loc);
            ourChoice->setRank(0);
            ourChoice->setPrimeMover(loc);
            ourChoice->setActiveParticipants(1);
        }
        
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}

/**
 myCompare compares two locations to see which is best

 if they equal in pollution levels pick location with most sugar
 else pick least polluted

 @param a :pointer to location
 @param b :pointer to location
 @returns true if a better than b
 @exception none
 */
int AgentBasicMove::myCompare(Location *a, Location *b){
    if (a->getPollution()==b->getPollution()) {
        return a->getWealth() - b->getWealth();//I am assuming we will only be checking empty locations
    } else
    {
        return a->getPollution() - b->getPollution();
    }
}
