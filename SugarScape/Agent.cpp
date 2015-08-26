//
//  Agent.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//
#include "World.h"

#include "Agent.h"

//Constructors
Agent::Agent(World *s,Agent *dad, Agent *mum, std::pair<int,int> pos):amountEaten(0), done(false),
    father(dad),mother(mum),killed(false),newPosition(pos),currentPosition(pos),
    theWorld(s),currentAge(0),newAge(1),vision(2),
    cultureLength(s->getCultureCount()),immunityLength(s->getImmunityLength())
{
    if (dad==nullptr) {
        newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
        newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax() );
        maxAge=theWorld->getRnd(theWorld->getMinAge(), theWorld->getMaxAge());
        currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),theWorld->getMaxMetabolism());
        //currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),theWorld->getMaxSpiceMetabolism());
    }
    else{
        newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
        newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax() );
        maxAge=theWorld->getRnd(theWorld->getMinAge(), dad->getMaxAge());
        currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),mum->getMetabolism());
        //currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),mum->getSpiceMetabolism());
    }
    if (theWorld->getRnd(0,1)==0) {
        sex=Sex::male;
    }else{
        sex=Sex::female;
    }
    
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    /*!< Create random immunity */
    for (int i=0; i<immunityLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentImmunity.push_back(aBit);
        newImmunity.push_back(aBit);
    }
    /*!< Create random culture */
    for (int i=0; i<cultureLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentCulture.push_back(aBit);
        newCulture.push_back(aBit);
    }
    /*!< Create random disease */
    std::vector<bool> newDisease;
    for (int i=0; i<diseaseLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        newDisease.push_back(aBit);
    }
    currentDiseases.push_back(newDisease);
    newDiseases.push_back(newDisease);
}



//getters

bool Agent::getAvail(int direction){
    return availableNeighbours[direction];
}
int Agent::getAmountEaten(void){
    return amountEaten;
}

bool Agent::isDone(void){
    return done;
}
std::pair<int, int> Agent::getPosition(void){
    return currentPosition;
}
Sex Agent::getSex(void){
    return sex;
}
int Agent::getVision(void){
    return vision;
}
int Agent::getAge(void){
    return currentAge;
}
int Agent::getMaxAge(void){
    return maxAge;
}
int Agent::getMetabolism(void){
    return currentMetabolism;
}
int Agent::getSpiceMetabolism(void){
    return currentSpiceMetabolism;
}
int Agent::getSugar(void){
    return currentSugar;
}
int Agent::getSpice(void){
    return currentSpice;
}
int Agent::getWealth(void){
    return currentSugar+currentSpice;
}
int Agent::getReward(void){
    return std::min(this->getWealth(),theWorld->getCombatLimit());
}
int Agent::getCultureLength(void){
    return cultureLength;
}
int Agent::getImmunityLength(void){
    return immunityLength;
}
unsigned long Agent::getChildrenCount()
{
    return currentChildren.size();
}
Agent* Agent::getFather()
{
    return father;
}
Agent* Agent::getMother()
{
    return mother;
}


std::vector<bool> Agent::getCulture(void){
    return currentCulture;
}
std::vector<bool> Agent::getImmunity(void){
    return currentImmunity;
}
std::vector<Agent*> Agent::getChildren(void){
    return currentChildren;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwed(void){
    return currentLoansOwed;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwing(void){
    return currentLoansOwing;
}
std::vector<std::vector<bool>> Agent::getDiseases(void){
    return currentDiseases;
}
Location* Agent::getLocation(void){
    return theWorld->getLocation(currentPosition);
}
//setters

bool Agent::markNeighbour(int direction)
{
    return availableNeighbours[direction]=false;
}


std::pair<int, int> Agent::setPosition(std::pair<int, int> destination){
    newPosition.first=theWorld->wrap(destination.first);
    newPosition.second=theWorld->wrap(destination.second);
    return newPosition;
}
Sex Agent::setSex(Sex newSex){
    if (sex==Sex::unknown) sex=newSex;
    return sex;
}
int Agent::setVision(int newVision){
    if (vision==-1) {
        vision=newVision;
    }
    return newVision;
}
int Agent::incAge(void){
    return ++currentAge;
}
int Agent::setAge(int newAmount){
    currentAge=newAmount;
    return currentAge;
}
int Agent::setMaxAge(int newMax){
    if (maxAge==-1) {
        maxAge=newMax;
    }
    return maxAge;
}
int Agent::setMetabolism(int newAmount){
    newMetabolism=newAmount;
    return newMetabolism;
}
int Agent::setSpiceMetabolism(int newAmount){
    newSpiceMetabolism=newAmount;
    return newSpiceMetabolism;
}
int Agent::incSugar(int extraSugar){
    newSugar+=extraSugar;
    return newSugar;
}
int Agent::incSpice(int extraSpice){
    newSpice+=extraSpice;
    return newSpice;
}
int Agent::setSugar(int newAmount){
    newSugar=newAmount;
    return newSugar;
}
int Agent::setSpice(int newAmount){
    newSpice=newAmount;
    return newSpice;
}
int Agent::setCultureLength(int newAmount){
    cultureLength=newAmount;
    return cultureLength;
}
int Agent::setImmunityLength(int newAmount){
    immunityLength=newAmount;
    return immunityLength;
}
int Agent::setImmunityTag(bool newValue,int index){
    newImmunity[index]=newValue;
    return newImmunity[index];
}
std::vector<bool> Agent::setCulture(std::vector<bool> replacementCulture){
    newCulture=replacementCulture;
    return newCulture;
}
std::vector<bool> Agent::setImmunity(std::vector<bool> replacementImmunity){
    newImmunity=replacementImmunity;
    return newImmunity;
}
std::vector<Agent*> Agent::setChildren(std::vector<Agent*>replacementChildren){
    newChildren=replacementChildren;
    return newChildren;
}

std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwed){
    newLoansOwed=replacementLoansOwed;
    return newLoansOwed;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwing){
    newLoansOwing=replacementLoansOwing;
    return newLoansOwing;
}
std::vector<std::vector<bool>> Agent::setDiseases(std::vector<std::vector<bool>> replacementDiseases){
    newDiseases=replacementDiseases;
    return newDiseases;
}

//*********************** HELPERS ***********************************************


Agent* Agent::initialise(World *sim,Agent *dad, Agent *mum)
{
    theWorld=sim;
    father=dad;
    mother=mum;
    done=false;
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    currentAge=newAge=0;
    return this;
}

Agent* Agent::reincarnate(std::pair<int,int> pos){
    mother=father=nullptr;
    killed=false;
    newPosition=currentPosition=pos;
    currentAge=0;
    newAge=1;
    vision=theWorld->getRnd(0, theWorld->getMaxVision());
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
    newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax());
    maxAge=theWorld->getRnd(theWorld->getMinAge(), theWorld->getMaxAge());
    currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),theWorld->getMaxMetabolism());
    currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),theWorld->getMaxSpiceMetabolism());
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    /*!< Create random immunity */
    for (int i=0; i<immunityLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentImmunity.push_back(aBit);
        newImmunity.push_back(aBit);
    }
    /*!< Create random culture */
    for (int i=0; i<cultureLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentCulture.push_back(aBit);
        newCulture.push_back(aBit);
    }
    /*!< Create random disease */
    std::vector<bool> newDisease;
    for (int i=0; i<diseaseLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        newDisease.push_back(aBit);
    }
    currentDiseases.push_back(newDisease);
    newDiseases.push_back(newDisease);
    return this;
}


bool Agent::markDone(void){
    return done=true;
}

bool Agent::markKilled(){
    return killed=true;
}

affiliation Agent::getTribe(void){
    int reds=0;
    for (int i=0; i<cultureLength; ++i) {
        if (currentCulture[i]==true) {
            reds++;
        }
    }
    if (reds>cultureLength/2) {
        return affiliation::red;
    }
    else{
        return affiliation::blue;
    }
}
bool Agent::isImmune(std::vector<bool> disease){
    int j=0;
    int length= (int)disease.size();
    for (int i=0; i<immunityLength-length; ++i) {
        for (j=0; j<length && disease[j]==currentImmunity[i+j]; ++j) {
            if (i+j==immunityLength-1) {
                return false;
            }
        }
        if (j==length) {
            return true;
        }
    }
    return false;
}
bool Agent::isChild(Agent* agent){
    for (const Agent* child: currentChildren){
        if (agent==child) return true;
    }
    return false;
}
unsigned long Agent::addChild(Agent* newChild){
    newChildren.push_back(newChild);
    return newChildren.size();
}
unsigned long Agent::removeChild(Agent* goneChild){
    auto it = std::find(newChildren.begin(), newChildren.end(), goneChild);
    if(it != newChildren.end())
        newChildren.erase(it);
    return newChildren.size();
}
int Agent::totalOwed(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}
int Agent::totalOwing(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}
int Agent::OwedToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}


int Agent::OwingToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}
/**
 * Checks to see if an agent has a particular disease
 * @param infection :disease we are checking for
 * @return true if we have it otherwise false
 * @exception none
 */
bool Agent::hasDisease(std::vector<bool> infection){
    for(const std::vector<bool> myDisease:currentDiseases){
        if (myDisease==infection) {
            return true;
        }
    }
    return false;
}

/**
 * Infects an agent with a disease by adding it to the list of diseases agent has. Be careful not to add the same disease multiple times
 * @param infection :Bool array representing a disease
 * @return the number of diseases held by the agent
 * @exception none
 */
unsigned long Agent::addDisease(std::vector<bool> infection){
    newDiseases.push_back(infection);
    return newDiseases.size();
}



unsigned long Agent::diseaseCount(void){
    return currentDiseases.size();
}

/**
 * Sets the value of one of the bools in the culture array
 * @param index :index of tag being updated
 * @param value :new value of tag
 * @return new tag value
 * @exception none
 */
bool Agent::setTag(int index,bool value){
    return newCulture[index]=value;
}

/**
 * Tells us if an agent is dead -- if it has reached maxAge or has no sugar left
 * @return true if will die now else false
 * @exception none
 */
bool Agent::isDead(void)
{
    if (currentAge>=maxAge || currentSugar<=0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Tells us if an agent is marked for dead via combat
 * @return true if will be killed in combat now else false
 * @exception none
 */
bool Agent::isKilled(void)
{
    return killed;
}

/**
 * Removes all loans with dead agents
 * @return number of loan agreements nullified
 * @exception none
 */
int Agent::removeDeadLoans(void)
{
    int repititions=0;
    auto it=newLoansOwed.begin();
    while(it!=newLoansOwed.end())
    {
        if (it->first->isDead()) {
            it=newLoansOwed.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    it=newLoansOwing.begin();
    while(it!=newLoansOwing.end())
    {
        if (it->first->isDead()) {
            it=newLoansOwing.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    return repititions;
}

/**
 * Removed link to mother if father is dead
 * @return true if mother was dead else false
 * @exception none
 */
bool Agent::removeDeadMother(void)
{
    if (mother==nullptr) {
        return true;
    }
    else if (mother->isDead()) {
        mother=nullptr;
        return true;
    }
    else{
        return false;
    }
}
/**
 * Removed link to father if father is dead
 * @return true if father was dead else false
 * @exception none
 */
bool Agent::removeDeadFather(void)
{
    if (father==nullptr) {
        return true;
    }
    else if (father->isDead()) {
        father=nullptr;
        return true;
    }
    else{
        return false;
    }
}
/**
 * Removes all loans with dead agents
 * @return number of loan agreements nullified
 * @exception none
 */
int Agent::removeKilledLoans(void)
{
    int repititions=0;
    auto it=newLoansOwed.begin();
    while(it!=newLoansOwed.end())
    {
        if (it->first->isKilled()) {
            it=newLoansOwed.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    it=newLoansOwing.begin();
    while(it!=newLoansOwing.end())
    {
        if (it->first->isKilled()) {
            it=newLoansOwing.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    return repititions;
}

/**
 * Removed link to mother if mother is dead
 * @return true if mother was dead else false
 * @exception none
 */
bool Agent::removeKilledMother(void)
{
    if (mother==nullptr) {
        return true;
    }
    else if (mother->isKilled()) {
        mother=nullptr;
        return true;
    }
    else{
        return false;
    }
}
/**
 * Removed link to father if father is dead
 * @return true if father was dead else false
 * @exception none
 */
bool Agent::removeKilledFather(void)
{
    if (father==nullptr) {
        return true;
    }
    else if (father->isKilled()) {
        father=nullptr;
        return true;
    }
    else{
        return false;
    }
}


bool Agent::allDone(void){
    for (int i=0; i<4; ++i) {
        if (availableNeighbours[i]==true) {
            return false;
        }
    }
    return true;
}

bool Agent::resetNeighbours(void){
    for (int i=0; i<4; ++i) {
        availableNeighbours[i]=true;
    }
    return true;
}

bool Agent::makeUnavailable(void){
    for (int i=0; i<4; ++i) {
        availableNeighbours[i]=false;
    }
    return true;
}
/**
 * Finalises updates - Applies updates to agent state
 * @return true if update sucessfull, otherwise false
 * @exception none
 */
bool Agent::sync(void){
    currentPosition=newPosition;
    currentSugar=newSugar-currentMetabolism;
    currentSpice=newSpice-currentSpiceMetabolism;
    for (int i=0; i<cultureLength; ++i) {
        currentCulture[i]=newCulture[i];
    }
    for (int i=0; i<immunityLength; ++i) {
        currentImmunity[i]=newImmunity[i];
    }
    currentChildren=newChildren;
    currentLoansOwed=newLoansOwed;
    currentLoansOwing=newLoansOwing;
    currentDiseases=newDiseases;
    currentAge = newAge++;
    done=false;
    killed = false;
    return true;
}

