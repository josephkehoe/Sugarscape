//
//  World.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "World.h"
#include "group.h"
#include "Action.h"



//Constructor
World::World(void)
    :size(DIM),step(0),cultureCount(CultureCount),
    maxAge(MaxAge),maxVision(MaxVision),maxMetabolism(MaxMetabolism),
    minAge(MinAge),minMetabolism(MinMetabolism),sugarGrowth(SugarGrowth),
    duration(Duration),rate(Rate),initialPopulationSize(InitialPopulationSize),
    initialSugarMax(InitialSugarMax),initialSugarMin(InitialSugarMin),winterRate(WinterRate),
    seasonLength(SeasonLength),production(Production),consumption(Consumption),
    combatLimit(CombatLimit),immunityLength(ImmunityLength),pollutionRate(PollutionRate),
    childAmount(ChildAmount)
{
    //Create Locations in Lattice
    Lattice=new Location[size*size];
//    for (int i=0; i<size; ++i) {
//        Lattice[i]=new Location[size];
//    }//for
    for (int i=0; i<size*size; ++i) {
            Lattice[i].setWorld(this);
    }
     rng.seed();
    //create agents and put in lattice
    std::pair<int,int> pos;
    for (int i=0; i<size*size/4; ++i) {//quatar fill lattice
        Agent *anAgent= new Agent(this,nullptr,nullptr);
        do {
            pos.first=getRnd(0, size-1);
            pos.second=getRnd(0,size-1);
        } while (Lattice[pos.first*size+pos.second].hasAgent());
        anAgent->setPosition(pos);
        Lattice[pos.first*size+pos.second].setAgent(anAgent);
        population.push_back(anAgent);
    }
}

//Destructor
World::~World(){
    delete [] Lattice;
    
}


//*************************Getters*************************


int World::getRnd(int start,int end){
    std::uniform_int_distribution<uint32_t> uint_dist(start,end);
    return uint_dist(rng);
}

/**
 Returns the step number
 @returns step
 @exception void
 */
int World::getStep(void){
    return step;
}
/**
 Returns the dimensions of the lattice
 @returns size
 @exception void
 */
int World::getSize(void){
    return size;
}
/**
 Returns the size of the culture string
 @returns cultureCount
 @exception void
 */
int World::getCultureCount(void){
    return cultureCount;
}
/**
 Returns the size of a disease string
 @returns cultureCount
 @exception void
 */
int World::getDiseaseLength(void){
    return diseaseLength;
}
/**
 Returns the maximum possible vision length of any agent
 @returns maxVision
 @exception void
 */
int World::getMaxVision(void){
    return maxVision;
}
/**
 Returns the minimum possible metabolism rate for any agent
 @returns minMetabolism
 @exception void
 */
int World::getMinMetabolism(void){
    return minMetabolism;
}
/**
 Returns the maximum possible metbolism rate for any agent
 @returns maxMetabolism
 @exception void
 */
int World::getMaxMetabolism(void){
    return maxMetabolism;
}
/**
 Returns the growth rate for each location
 @returns sugarWrowth
 @exception void
 */
int World::getSugarGrowth(void){
    return sugarGrowth;
}
/**
 Returns the minimum possible natural lifespan of an agent
 @returns minAge
 @exception void
 */
int World::getMinAge(void){
    return minAge;
}
/**
 Returns the maximum possible natural lifespan of an agent
 @returns maxAge
 @exception void
 */
int World::getMaxAge(void){
    return maxAge;
}
/**
 Returns the duraion of a loan
 @returns duration
 @exception void
 */
int World::getDuration(void){
    return duration;
}
/**
 Returns the rate of interest for a load
 @returns rate
 @exception void
 */
int World::getRate(void){
    return rate;
}
/**
 Returns the minimum possible initial sugar allocation assigned to an agent
 @returns initialSugarMin
 @exception void
 */
int World::getInitialSugarMin(void){
    return initialSugarMin;
}
/**
 Returns the maximum possible initial sugar allocation assigned to an agent
 @returns initialSugarMax
 @exception void
 */
int World::getInitialSugarMax(void){
    return initialSugarMax;
}
/**
 Returns the winter growth rate for each location
 @returns winterRate
 @exception void
 */
int World::getWinterRate(void){
    return winterRate;
}
/**
 Returns the length of each season
 @returns seasonLength
 @exception void
 */
int World::getSeasonLength(void){
    return seasonLength;
}
/**
 Returns the amount of pollution generated by activity
 @returns production :integer
 @exception void
 */
int World::getProduction(void){
    return production;
}
int World::getConsumption(void){
    return consumption;
}
int World::getCombatLimit(void){
    return combatLimit;
}
int World::getImmunityLength(void){
    return immunityLength;
}
int World::getInitialPopulationSize(void){
    return initialPopulationSize;
}
int World::getPollutionRate(void){
    return pollutionRate;
}
int World::getChildAmount(void){
    return childAmount;
}
Agent* World::getAgent(std::pair<int,int> pos){
    return Lattice[(pos.first%size)*size+(pos.second%size)].getAgent();
}
std::vector<Location*> World::getNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.first) {
            neighbourhood.push_back(&Lattice[(i%size)*size+pos.second]);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.second) {
            neighbourhood.push_back(&Lattice[(pos.first*size)+i%size]);
        }//if
    }//for
    return neighbourhood;
}

/**
 * get all empty locations around us that are not marked done
 * @param pos :x,y-coordinates of index
 * @param range :vision - how far we can see in four directions
 * @return vector of Location pointers (all empty locations in our neighbourhood
 */
std::vector<Location*> World::getEmptyNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.first && Lattice[(i%size)*size+pos.second].hasAgent()==false && Lattice[(i%size)*size+pos.second].isDone()==false) {
            neighbourhood.push_back(&Lattice[(i%size)*size+pos.second]);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.second && false==Lattice[(pos.first*size)+i%size].hasAgent() && false==Lattice[(pos.first*size)+i%size].isDone()) {
            neighbourhood.push_back(&Lattice[(pos.first*size)+i%size]);
        }//if
    }//for
    return neighbourhood;
}


/**
 * get all empty or attackable locations around us that are not marked done
 * @param pos :x,y-coordinates of index
 * @param range :vision - how far we can see in four directions
 * @return vector of Location pointers (all empty locations in our neighbourhood
 */
std::vector<Location*> World::getCombatNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.first && Lattice[(i%size)*size+pos.second].isDone()==false) {
            if (Lattice[(i%size)*size+pos.second].hasAgent()==false )
            {
                neighbourhood.push_back(&Lattice[(i%size)*size+pos.second]);
            }else {
                Agent *me=Lattice[pos.first*size+pos.second].getAgent();
                Agent *other=Lattice[(i%size)*size+pos.second].getAgent();
                if (me->getCulture()!=other->getCulture() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[(i%size)*size+pos.second]);
                }
            }
            
        }//if
    }//for
    
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.second && false==Lattice[pos.first*size+i%size].isDone())
        {
            if (false==Lattice[pos.first*size+i%size].hasAgent()) {
                neighbourhood.push_back(&Lattice[pos.first*size+i%size]);
            }else {
                Agent *me=Lattice[pos.first*size+pos.second].getAgent();
                Agent *other=Lattice[pos.first*size+i%size].getAgent();
                if (me->getCulture()!=other->getCulture() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[pos.first*size+i%size]);
                }
            }
        }//if
    }//for
    return neighbourhood;
}



/**
 * Returns all agents in our neighbourhood who are not marked as done!
 * @param xPosition :x-xoordinate of index
 * @param yPosition :y-coordinate of index
 * @param range :vision - how far we can see in four directions
 * @return vector of pointers to agents who are neighbours and not marked done
 */
std::vector<Agent*> World::getNeighbours(std::pair<int,int> pos,int range)
{
    std::vector<Agent*> neighbourList;
    Agent* neighbour=nullptr;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        neighbour=Lattice[(i%size)*size+pos.second].getAgent();
        if (neighbour!=nullptr && i!=pos.first && Lattice[(i%size)*size+pos.second].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        neighbour=Lattice[pos.first*size+i%size].getAgent();
        if (neighbour!=nullptr && i!=pos.second && Lattice[pos.first*size+i%size].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    return neighbourList;
}
Location* World::getLattice(void)
{
    return Lattice;
}
Location* World::getLocation(std::pair<int, int> pos)
{
    return &Lattice[(pos.first%size)*size+(pos.second%size)];
}



//Setters
int World::setSize(int newSize){
    size=newSize;
    return size;
}
int World::setCultureCount(int newCultureCount){
    cultureCount=newCultureCount;
    return cultureCount;
}
int World::setDiseaseLength(int newDiseaseLength){
    diseaseLength=newDiseaseLength;
    return diseaseLength;
}
int World::setMaxVision(int newMaxVision){
    maxVision=newMaxVision;
    return maxVision;
}
int World::setMinMetabolism(int newMinMetabolism){
    minMetabolism=newMinMetabolism;
    return minMetabolism;
}
int World::setMaxMetabolism(int newMaxMetabolism){
    maxMetabolism=newMaxMetabolism;
    return maxMetabolism;
}
int World::setSugarGrowth(int newSugarGrowth){
    sugarGrowth=newSugarGrowth;
    return sugarGrowth;
}
int World::setMinAge(int newMinAge){
    minAge=newMinAge;
    return minAge;
}
int World::setMaxAge(int newMaxAge){
    maxAge=newMaxAge;
    return maxAge;
}
int World::setDuration(int newDuration){
    duration=newDuration;
    return duration;
}
int World::setRate(int newRate){
    rate=newRate;
    return rate;
}
int World::setInitialSugarMin(int newInitialSugarMin){
    initialSugarMin=newInitialSugarMin;
    return initialSugarMin;
}
int World::setInitialSugarMax(int newInitialSugarMax){
    initialSugarMax=newInitialSugarMax;
    return initialSugarMax;
}
int World::setWinterRate(int newWinterRate){
    winterRate=newWinterRate;
    return winterRate;
}
int World::setSeasonLength(int newSeasonLength){
    seasonLength=newSeasonLength;
    return seasonLength;
}
int World::setProduction(int newProduction){
    production=newProduction;
    return production;
}
int World::setConsumption(int newConsumption){
    consumption=newConsumption;
    return consumption;
}
int World::setCombatLimit(int newCombatLimit){
    combatLimit=newCombatLimit;
    return combatLimit;
}
int World::setImmunityLength(int newImmunityLength){
    immunityLength=newImmunityLength;
    return immunityLength;
}
int World::setInitialPopulationSize(int newInitialPopulationSize){
    initialPopulationSize=newInitialPopulationSize;
    return initialPopulationSize;
}
int World::setPollutionRate(int newPollutionRate){
    pollutionRate=newPollutionRate;
    return pollutionRate;
}
int World::setChildAmount(int newChildAmount){
    childAmount=newChildAmount;
    return childAmount;
}
Agent* World::setAgent(std::pair<int,int> pos, Agent *newAgent){
    return Lattice[(pos.first%size)*size+pos.second%size].setAgent(newAgent);
}
Agent* World::killAgent(std::pair<int,int> pos)
{
    if (Lattice[(pos.first%size)*size+pos.second%size].hasAgent()) {
        return Lattice[(pos.first%size)*size+pos.second%size].killAgent();
    }
    else
    {
        return nullptr;
    }
}
//Rule Application


int World::addRule(Action* rule){
    activeRules.push_back(rule);
    return (int)activeRules.size();
}

int World::applyRules(){
    int ruleCount=0;
    for(auto rule:activeRules){
        ruleCount+=rule->run(0,0,size);
    }
    return ruleCount;
}
