//
//  AgentDisease.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 21/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentDisease.h"
/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentDisease::AgentDisease(World *sim,Strategy* theStrategy):Action(sim,theStrategy){//ReadAction
    //EMPTY
}

/**
 * If agent X resides at this location find its neighbours and collect diseases from them
 * then update agent X's immunity tags for these diseases
 * @param loc :Location we are checking
 * @see Disease Rule
 * @return True if agent was here
 * @exception none
 */
bool AgentDisease::executeAction(Location *loc, group* grp){

    if (loc->hasAgent()) {
        Agent * subject=loc->getAgent();
        //Add one disease from each neighbour
        std::vector<Agent*> neighbours=sim->getNeighbours(loc->getPosition(), 1);
        for(auto a:neighbours){
            if (a->diseaseCount()>0) {
                std::vector<bool>* rndDisease = a->getRndDisease();
                if (!subject->hasDisease(rndDisease) && !subject->isImmune(rndDisease)) {
                    if (subject->diseaseCount()<sim->getMaxDiseaseCount())
                        subject->addDisease(rndDisease);//new disease contracted
                }
            }
            
        }
        //check immunity and update immunity tags
        std::vector<bool> immunity=subject->getImmunity();
        for(auto infection:subject->getDiseases()){
            if (!subject->isImmune(infection)) {
                /*!
                 * TODO: Here is where we take one from sugerlevel
                 * metabolism penalty of one for every infection we are not immune from
                 */
                int bestIndex=0;
                int bestHammingDistance=(int)infection->size()+1;
                /*!
                 Check each substring for Hamming distance
                 */
                for (int startIndex=0; startIndex<immunity.size()-infection->size(); ++startIndex) {
                    /*!
                     Calculate Hamming distance of current substring
                     */
                    int currentScore=0;
                    for (int k=0; k<infection->size(); ++k) {
                        if ((*infection)[k]!=immunity[k+startIndex]) {
                            ++currentScore;
                        }
                    }
                    /*!
                     Is current substring the closest so far?
                     */
                    if (currentScore<bestHammingDistance) {
                        bestHammingDistance=currentScore;
                        bestIndex=startIndex;
                    }
                }
                if (bestHammingDistance==0) std::cout << "ERROR IN HAMMING DISTANCE FUNCTION" <<  std::endl;
                else {//find first tag not agreeing
                    int i = 0;
                    for (i = 0; immunity[bestIndex + i] == (*infection)[i]; ++i) {
                        //EMPTY
                    }
                    //set tag at index value to new value
                    subject->setImmunityTag((*infection)[i], bestIndex + i);
                }
            }//foreach infection
        }
        return true;//agent updated
    }else{//no agent here
        return false;//we did nothing
    }

    
    
}
