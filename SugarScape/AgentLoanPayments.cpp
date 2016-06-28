//
//  AgentLoanPayments.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 12/10/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentLoanPayments.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
AgentLoanPayments::AgentLoanPayments(World *sim,Strategy *theStrategy)
:Action(sim,theStrategy)//WriteAction
{
    //our work is done
}



bool AgentLoanPayments::executeAction(Location * loc, group * grp)
{
    if (loc->hasAgent()) {
        std::vector<std::pair<Agent*,std::pair<int, int>>> newLoans;
        Agent* theAgent=loc->getAgent();
        auto theLoanBook=theAgent->getLoansOwed();
        int amtAvail=theAgent->getSugar();
        /*!< find all loans due to be paid back --if any */
        for(const std::pair<Agent*,std::pair<int, int>> account:theLoanBook){
            if (account.second.second==sim->getStep()) {
                Agent* theLender=account.first;
                int amtDue=account.second.first+account.second.first*sim->getRate()*sim->getDuration();
                if (amtDue<amtAvail){
                    amtAvail=amtAvail-amtDue;
                    theLender->incSugar(amtDue);
                }
                else{
                    theLender->incSugar(amtAvail/2);
                    amtAvail=amtAvail/2;
                    theAgent->addLoanOwed(theLender,amtAvail/2);//XXX <--CREATE RENEGOTIATED LOAN
                    theLender->addLoanOwing(theAgent,amtAvail/2);
                }
            }//if loan due
        }//end for
        theAgent->setSugar(amtAvail);
        theAgent->removePaidLoans();/*!<remove paid off loans and also any loans due to use (as they will be paid to
 * us this turn anyway */
        return true;
    }else{
        return false;/*!< no agent present or no loans due so did nothing */
    }
}



group* AgentLoanPayments::formGroup(Location *loc)
{
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {/*!< Agent at this location */
        ourChoice = new group();
        ourChoice->setPrimeMover(loc);
        ourChoice->setActiveParticipants(1);/*!< one active participant per group - the agent */
        ourChoice->setRank(0);
        Agent* theAgent=loc->getAgent();
        auto theLoanBook=theAgent->getLoansOwed();
        /*!< find all loans due to be paid back */
        for(const std::pair<Agent*,std::pair<int, int>> account:theLoanBook){
            if (account.second.second==sim->getStep()) {
                ourChoice->push_back(account.first->getLocation());
            }//if
        }
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}