//
//  World.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "World.h"


//Constructors
World::World(void)
    :size(20),step(0),cultureCount(20),
    maxAge(20),maxVision(6),maxMetabolism(5),
    minAge(10),minMetabolism(1),sugarGrowth(10),
    duration(10),rate(3),initialPopulationSize(50),
    initialSugarMax(10),initialSugarMin(5),winterRate(3),
    seasonLength(5),production(2),consumption(2),
    combatLimit(6),immunityLength(30),pollutionRate(2),
    childAmount(4)
{
    Lattice=new Location*[size];
    for (int i=0; i<size; ++i) {
        Lattice[i]=new Location[size];
    }//for
    
}




//*************************Getters*************************

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
 Returns the ...
 @returns <#retval#>
 @exception <#throws#>
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
Agent* World::getAgent(int xPosition,int yPosition){
    return Lattice[xPosition%size][yPosition%size].getAgent();
}
std::vector<Agent*> World::getNeighbours(int xPosition,int yPosition,int range){
    std::vector<Agent*> neighbourList;
    Agent* neighbour=nullptr;
    for (int i=xPosition-range; i<xPosition+range; ++i) {
        neighbour=Lattice[i%size][yPosition].getAgent();
        if (neighbour!=nullptr && i!=xPosition) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    for (int i=yPosition-range; i<yPosition+range; ++i) {
        neighbour=Lattice[xPosition][i%size].getAgent();
        if (neighbour!=nullptr && i!=yPosition) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    return neighbourList;
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
Agent* World::setAgent(int xPosition,int yPosition, Agent *newAgent){
    return Lattice[xPosition%size][yPosition%size].setAgent(newAgent);
}
//Rule Application
int World::doIndependentRule(Action* upDate){
    //Perform action
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            upDate->execute(Lattice[i][k]);
        }
    }
    //Update everyone
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            Lattice[i][k].sync();
            if (Lattice[i][k].hasAgent()) {
                Lattice[i][k].getAgent()->sync();
            }
        }
    }
    return 1;
}
int World::doReadDependentRule(Action* upDate){
    //Perform action
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            upDate->execute(Lattice[i][k]);
        }
    }
    //Update everyone
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            Lattice[i][k].sync();
            if (Lattice[i][k].hasAgent()) {
                Lattice[i][k].getAgent()->sync();
            }
        }
    }
    return 1;
}
int World::doWriteDependentRule(Action* upDate, Action* getGroup){
    return -1;
}
