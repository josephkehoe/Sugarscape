//
// Created by joseph on 24/08/16.
//

#include "AgentMoveClosest.h"


/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentMoveClosest::AgentMoveClosest(World *sim, Strategy *theStrategy)
        :AgentBasicMove(sim,theStrategy)
{
    //our work is done
}

/**
 pickIndex returns best location to move to

 Sorts vector of possible destinations and picks highest ranking one
 @param possibleDestinations :vector of possible destinations
 @returns index of first destination in sorted vector (the best)
 @exception none
 */
int AgentMoveClosest::pickIndex(std::vector<Location*> possibleDestinations)
{
    int best=0;
    for (unsigned int i=0; i<possibleDestinations.size(); ++i) {
        if (myCompare(possibleDestinations[i], possibleDestinations[best])>0) {
            best=i;
        }
        else if (myCompare(possibleDestinations[i], possibleDestinations[best])==0) {
            if (sim->getRnd(0,10)>5) best=i;//if equal pick one by coin flip
        }
    }
    //std::sort(possibleDestinations.begin(),possibleDestinations.end(),myCompare);
    return best;
}

/**
 * Pick a random empty location within our neighbourhood as defined by our vision
 *
 * Ranks chosen move by proximity to current position
 * @param loc :Our location
 * @see Move Rule
 * @return Our chosen location held in a group object (or our existing location if we have no move)
 * @exception none
 */
group* AgentMoveClosest::formGroup(Location *loc)
{
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {/*!< Agent at this location */
        ourChoice = new group();
        Agent* theAgent=loc->getAgent();
        std::vector<Location*> possibleDestinations=sim->getEmptyNeighbourhood(theAgent->getPosition(), theAgent->getVision());/*!< find all empty locations */
        if (possibleDestinations.size()!=0) {/*!< check to see if we can move anywhere */
            int index=pickIndex(possibleDestinations);
            int xdiff=possibleDestinations[index]->getPosition().first-theAgent->getPosition().first;
            int ydiff=possibleDestinations[index]->getPosition().second-theAgent->getPosition().second;
            if (xdiff<0) xdiff=-xdiff;
            if (ydiff<0) ydiff=-ydiff;
            int rank=xdiff+ydiff;/*!< Manhatten distance */
            ourChoice->push_back(possibleDestinations[index]);
            ourChoice->setRank(rank);
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
