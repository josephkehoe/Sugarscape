//
//  World.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include <QSettings>
#include <QString>
#include <fstream>
#include <chrono>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include "World.h"
#include "group.h"
#include "Action.h"
#include "Strategy.h"
#include "NewSweepStrategy.h"
#include "LineByLineStrategy.h"
#include "RndAsyncStrategy.h"
#include "IndependentStrategy.h"
#include "IterativeWriteStrategy.h"
#include "ReadDependentStrategy.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"
#include "AgentDeath.h"
#include "AgentDisease.h"
#include "Diffusion.h"
#include "AgentCombat.h"
#include "AgentReplacement.h"
#include "AgentMetabolism.h"
#include "AgentMating.h"
#include "AgentLoanPayments.h"
#include "AgentCredit.h"
#include "AgentInheritance.h"
#include "AgentMoveClosest.h"
#include "AgentMoveStrongest.h"



/**
 * Constructor Population is 1/4 lattice size
 * @param dimensionSize :length of lattice side Lattice[dimensionSize,dimensionSize]
 * @exception none
 */
World::World(int dimensionSize)
    : size(DIM), step(0), cultureCount(CULTURECOUNT),
      maxAge(MaxAge), maxVision(MaxVision), maxMetabolism(MaxMetabolism),
      minAge(MinAge), minMetabolism(MinMetabolism), sugarGrowth(SugarGrowth),
      duration(Duration), rate(Rate), initialPopulationSize(InitialPopulationSize),
      initialSugarMax(InitialSugarMax), initialSugarMin(InitialSugarMin), winterRate(WinterRate),
      initialSpiceMax(InitialSpiceMax), initialSpiceMin(InitialSpiceMin), spiceGrowth(SpiceGrowth),
      seasonLength(SeasonLength), production(Production), consumption(Consumption),
      combatLimit(CombatLimit), immunityLength(IMMUNITYLENGTH), pollutionRate(PollutionRate),
      childAmount(ChildAmount), diseaseLength(DISEASELENGTH), diseaseCount(DISEASECOUNT), initialPopulation
              (AGENTCOUNT), initialDiseaseCount(INITIALDISEASECOUNT)
{
    if (dimensionSize>0) {
        size=dimensionSize;
        //initialPopulation=size*size/4;
    }
    //seed random number generator!!
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    rng.seed(0);

    //Read INI file to set parameters for simulation
    this->readIniFile("config.ini");

    femaleFertilityStart=getRnd(MinFemaleFertilityStart, MaxFemaleFertilityStart+1);//range is inclusive!
    maleFertilityStart=getRnd(MinMaleFertilityStart, MaxMaleFertilityStart+1);//range is inclusive!
    femaleFertilityEnd=getRnd(MinFemaleFertilityEnd, MaxFemaleFertilityEnd+1);//range is inclusive!
    maleFertilityEnd=femaleFertilityEnd+10;//as per specification
    //create diseases
    for (int i = 0; i < diseaseCount; ++i) {
        int diseaseSize=getRnd(1,diseaseLength);
        std::cout << diseaseSize << std::endl;
        std::vector<bool>* newDisease = new std::vector<bool>;
        for (int j = 0; j < diseaseSize; ++j) {
            bool aBit=true;
            if (getRnd(0,10)>5){ aBit=false;}
            newDisease->push_back(aBit);
        }
        globalDiseaseList.push_back(newDisease);
    }
    Lattice=nullptr;
    /*!< Declare all possible strategies here */
    baseStrategy = new Strategy(this);
    newSweep= new NewSweepStrategy(this);
    lineByLine= new LineByLineStrategy(this);
    rndAsync= new RndAsyncStrategy(this);
    independent= new IndependentStrategy(this);
    iterativeWrite= new IterativeWriteStrategy(this);
    readDependent= new ReadDependentStrategy(this);
    writeDependent= new WriteStrategy(this);
    /*!< Declare all rules here */
    Rules[Growbk]= new Growback(this,independent);
    Rules[SeasonalGrowbk]= new SeasonalGrowback(this,independent);
    Rules[PollutionForm]= new PollutionFormation(this,independent);
    Rules[Diffuse]= new Diffusion(this,readDependent);
    Rules[BasicMovement]= new AgentBasicMove(this,writeDependent);
    Rules[Movement]= new AgentMove(this,writeDependent);
    Rules[ClosestMovement]= new AgentMoveClosest(this,writeDependent);
    Rules[StrongestMovement]= new AgentMoveStrongest(this,writeDependent);
    Rules[Combat]= new AgentCombat(this,writeDependent);
    Rules[Culture]= new AgentCulture(this,readDependent);
    Rules[Disease]= new AgentDisease(this,readDependent);
    Rules[Credit]= new AgentCredit(this,iterativeWrite);
    Rules[LoanPayments]= new AgentLoanPayments(this,iterativeWrite);
    Rules[Inheritance]= new AgentInheritance(this,writeDependent);
    Rules[Trade]= new AgentCredit(this,iterativeWrite);//TO DO: ADD AGENTTRADE
    Rules[Replacemt]= new AgentReplacement(this,writeDependent);
    Rules[Garbage]= new GarbageCollection(this,independent);
    Rules[Death]= new AgentDeath(this,readDependent);
    Rules[Reproduction]= new AgentMating(this,iterativeWrite);
    Rules[Metabolism]= new AgentMetabolism(this,independent);
    for(int i=0;i<RuleCount;++i){
        liveRules[i]=false;
    }
    liveRules[Garbage]=true;
    liveRules[Metabolism]=true;
    liveRules[Death]=true;
}

/**
 * Destructor - delete lattice array
 * @exception none
 */
World::~World(){
    if (Lattice!=nullptr) delete [] Lattice;
    for (auto aDisease: globalDiseaseList){
     delete aDisease;
    }
    delete baseStrategy;
    delete newSweep;
    delete lineByLine;
    delete rndAsync;
    delete independent;
    delete iterativeWrite;
    delete readDependent;
    delete writeDependent;
    for(int i=0;i<RuleCount;++i){
        delete Rules[i];
    }
    
}

//********************************HELPERS***************************************



/**
 * initialises World Sugar Levels and settings
 * @return true
 * @exception none
 */
bool World::init(std::string logFileName,std::string sugarFileName, std::string iniFile, int vision,int metabolism)
{
    //Open log file for error message output
    outputLog.open(logFileName,std::ios::out | std::ios::app);
    //Create Locations in Lattice
    if (Lattice!=nullptr) delete[] Lattice;
    Lattice=new Location[size*size];
    //read in initial sugar levels from config file
    int fileCount=this->readConfigFile(sugarFileName);
    for (int i=0; i<size*size; ++i) {
        Lattice[i].setWorld(this);
        Lattice[i].setPosition(std::pair<int,int>(i/size,i%size));
        //do not set these if we are reading in from config file -- only one assignment allowed!
        if (fileCount==0){
            Lattice[i].setMaxSugar(getRnd(InitialSugarMin, InitialSugarMax));
            Lattice[i].setSugar(getRnd(InitialSugarMin, Lattice[i].getMaxSugar()));
        }
    }

    //create agents and put in lattice
    std::pair<int,int> pos;
    for (int i=0; i<initialPopulation; ++i) {//quarter fill lattice
        Agent *anAgent= nullptr;
        do {
            pos.first=getRnd(0, size-1);
            pos.second=getRnd(0,size-1);
        } while (Lattice[pos.first*size+pos.second].hasAgent());
        anAgent=new Agent(this,nullptr,nullptr,pos);//,vision,metabolism);
        Lattice[pos.first*size+pos.second].initAgent(anAgent);
        //population.push_back(anAgent); NOT USED CURRENTLY
    }
    return true;
}

/**
 * Syncs dual state
 * @return zero
 * @exception none
 */
int World::sync(void){
//#pragma omp parallel for
// /*!< PUT PRAGMA BACK WITH CHECK FOR LOOP SIZE */
    for (int i=0; i<size*size; ++i) {
        Lattice[i].sync();
        if (Lattice[i].hasAgent()) Lattice[i].getAgent()->sync();
    }
    return 0;
}

/**
 * sanity check used during development
 * @return void
 * @exception none
 */
void World::sanityCheck(void){
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            if (Lattice[i*size+k].hasAgent()){
                std::cout << Lattice[i*size+k].getAgent()->getMetabolism()<<","<<Lattice[i*size+k].getAgent()->getSugar()<< ","
                <<Lattice[i*size+k].getAgent()->getAge() << ","<< Lattice[i*size+k].getAgent()->getMaxAge() <<std::endl;;
            }
        }
        
    }
    std::cout <<std::endl;
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            std::cout << Lattice[i*size+k].getSugar()<<" , ";
        }
        std::cout << std::endl;
    }
    std::cout <<std::endl;
}

/**
 * Handles wraparound on lattice. "%" does not work properly in C++ !
 * @param x :index in lattice
 * @see Lattice Definition
 * @return x after wraparound
 * @exception none
 */
int World::wrap(int x){
    if (x<0) {
         return size+x;
    } else if (x>=size){
        return x-size;
    }
    else {
        return x;
    }
}


/**
 * counts agents in lattice
 * @return number of agents
 * @exception none
 */
int World::getAgentCount(void){
    int count=0;
#pragma omp parallel for reduction(+:count)
    for (int i=0; i<size*size; ++i) {
            if (Lattice[i].hasAgent()){
                ++count;
            }
    }
    return count;
}


/**
 * counts blue agents in lattice
 * @return number of blue agents
 * @exception none
 */
int World::getBlueCount(void){
    int count=0;
#pragma omp parallel for reduction(+:count)
    for (int i=0; i<size*size; ++i) {
        if (Lattice[i].hasAgent()){
            if (Lattice[i].getAgent()->getTribe()==affiliation::blue) {
                ++count;
            }
        }
    }
    return count;
}

/**
 * set neighbours to not done, used in iterative write actions
 * @see InterativeAction
 * @return true
 * @exception none
 */
bool World::resetNeighbours(void){
#pragma omp parallel for
    for (int i=0; i<size*size; ++i) {
        if(Lattice[i].hasAgent()) Lattice[i].getAgent()->resetNeighbours();
    }
    return true;
}


//********************************GETTERS**************************************

/**
 * Increments step count by one
 * @return current step value
 * @exception none
 */
int World::incStep(){
    return ++step;
}

/**
 * Gets a randon number in range (inclusive)
 * @param start :integer start value of number range
 * @param end :integer end value in range
 * @return number in range [start, end] --inclusive!
 * @exception none
 */
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
 Returns the minimum possible spice metabolism rate for any agent
 @returns minMetabolism
 @exception void
 */
int World::getMinSpiceMetabolism(void){
    return minSpiceMetabolism;
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
 Returns the maximum possible spice metbolism rate for any agent
 @returns maxMetabolism
 @exception void
 */
int World::getMaxSpiceMetabolism(void){
    return maxSpiceMetabolism;
}
/**
 Returns the growth rate for each location
 @returns sugarGrowth
 @exception void
 */
int World::getSugarGrowth(void){
    return sugarGrowth;
}
/**
 Returns the growth rate for each location
 @returns spiceGrowth
 @exception void
 */
int World::getSpiceGrowth(void){
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
 Returns the minimum possible initial spice allocation assigned to an agent
 @returns initialSpiceMin
 @exception void
 */
int World::getInitialSpiceMin(void){
    return initialSpiceMin;
}
/**
 Returns the maximum possible initial spice allocation assigned to an agent
 @returns initialSpiceMax
 @exception void
 */
int World::getInitialSpiceMax(void){
    return initialSpiceMax;
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

/**
 * Gets consumptionvalue
 * @see Pollution
 * @return consumption value
 * @exception none
 */
int World::getConsumption(void){
    return consumption;
}

/**
 * Gets CombatLimit
 * @see AgentCombat
 * @return Combat Limit value
 * @exception none
 */
int World::getCombatLimit(void){
    return combatLimit;
}

/**
 * Gets length of immunity string
 * @see AgentDisease
 * @return immunity length
 * @exception none
 */
int World::getImmunityLength(void){
    return immunityLength;
}

/**
 * gets initial population size
 * @return Initial population size
 * @exception none
 */
int World::getInitialPopulationSize(void){
    return initialPopulationSize;
}

/**
 * Gets Pollution Rate
 * @see Pollution
 * @return Pollution Rate
 * @exception none
 */
int World::getPollutionRate(void){
    return pollutionRate;
}


/**
 * Gets Child Amount
 * @see AgentMating
 * @return Child Amount
 * @exception none
 */
int World::getChildAmount(void){
    return childAmount;
}

/**
 * Gets minimum age for female fertility
 * @see AgentMating,AgentCredit
 * @return minimum fertility age
 * @exception none
 */
int World::getFemaleMinFertilityAge(void){
    return femaleFertilityStart;
}

/**
 * Gets maximum age for female fertility
 * @see AgentMating,AgentCredit
 * @return maximum fertility age
 * @exception none
 */
int World::getFemaleMaxFertilityAge(void){
    return femaleFertilityEnd;
}

/**
 * Gets minimum age for male fertility
 * @see AgentMating,AgentCredit
 * @return minimum fertility age
 * @exception none
 */
int World::getMaleMinFertilityAge(void){
    return maleFertilityStart;
}

/**
 * Gets maximum age for female fertility
 * @see AgentMating,AgentCredit
 * @return maximum fertility age
 * @exception none
 */
int World::getMaleMaxFertilityAge(void){
    return maleFertilityEnd;
}

/**
 * Returns agent at position if any (or nullptr)
 * @param pos std::pair of location indices
 * @return pointer to agent at that position (or nullptr)
 * @exception none
 */
Agent* World::getAgent(std::pair<int,int> pos){
    return Lattice[wrap(pos.first)*size+wrap(pos.second)].getAgent();
}

/**
 * Returns number of diseases each agent is intialised with
 * @return int number of diseases
 * @exception none
 */
int World::getInitialDiseaseCount(void){
    return initialDiseaseCount;
}

int World::getMaxDiseaseCount(void){
    return diseaseCount;
}

/**
 * return all locations in neighbourhood
 * @param pos std::pair of position
 * @param range :size of neighbourhood (usually 1)
 * @return std::vector of all locations in neighbourhood
 * @exception none
 */
std::vector<Location*> World::getNeighbourhood(std::pair<int,int> pos,int range)
{
    std::vector<Location*> neighbourhood;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.first) {
            neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        if (i!=pos.second) {
            neighbourhood.push_back(&Lattice[(pos.first*size)+wrap(i)]);
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
    Location *loc=nullptr; //&Lattice[pos.first*size+pos.second];
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //std::cout << i <<"," << pos.second << "=" << wrap(i) << "*"<<wrap(pos.second) << "*" << wrap(i)*size+wrap(pos.second) << std::endl;
        //pick location only if it !=identity (us) and is empty and is not marked done
        loc=&Lattice[wrap(i)*size+wrap(pos.second)];
        if (loc->hasAgent()==false && loc->isDone()==false) {
            neighbourhood.push_back(loc);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        loc=&Lattice[(pos.first*size)+wrap(i)];
        if (false==loc->hasAgent() && false==loc->isDone()) {
            neighbourhood.push_back(loc);
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
    Agent *me=Lattice[pos.first*size+pos.second].getAgent();
    Agent *other=nullptr;
    for (int i=pos.first-range; i<=pos.first+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.first && Lattice[wrap(i)*size+pos.second].isDone()==false) {
            if (Lattice[wrap(i)*size+pos.second].hasAgent()==false )
            {
                neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
            }else {
                other=Lattice[wrap(i)*size+pos.second].getAgent();
                if (me->getTribe()!=other->getTribe() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[wrap(i)*size+pos.second]);
                }
            }
            
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        //pick location only if it !=identity (us) and is empty and is not marked done
        if (i!=pos.second && false==Lattice[pos.first*size+wrap(i)].isDone())
        {
            if (false==Lattice[pos.first*size+wrap(i)].hasAgent()) {
                neighbourhood.push_back(&Lattice[pos.first*size+wrap(i)]);
            }else {
                other=Lattice[pos.first*size+wrap(i)].getAgent();
                if (me->getTribe()!=other->getTribe() && me->getWealth()>other->getWealth())
                {
                    neighbourhood.push_back(&Lattice[pos.first*size+wrap(i)]);
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
        neighbour=Lattice[wrap(i)*size+pos.second].getAgent();
        if (neighbour!=nullptr && i!=pos.first && Lattice[wrap(i)*size+pos.second].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    for (int i=pos.second-range; i<=pos.second+range; ++i) {/*!< loop up to and including (<=) or else we lose last location */
        neighbour=Lattice[pos.first*size+wrap(i)].getAgent();
        if (neighbour!=nullptr && i!=pos.second && Lattice[pos.first*size+wrap(i)].isDone()==false) {
            neighbourList.push_back(neighbour);
        }//if
    }//for
    return neighbourList;
}

/**
 * Return lattice array
 * @return lattice array (ptr)
 * @exception none
 */
Location* World::getLattice(void)
{
    return Lattice;
}
/**
 * get location at position
 * @param pos :std::pair position indices
 * @return pointer to location
 * @exception none
 */
Location* World::getLocation(std::pair<int, int> pos)
{
    return &Lattice[wrap(pos.first)*size+wrap(pos.second)];
}

std::vector<bool>*  World::getRandomDisease(void)
{
    return globalDiseaseList[getRnd(0,globalDiseaseList.size()-1)];
}

//**************************SETTERS********************************


/**
 * change size of lattice dimensions
 * @param newSize
 * @return old Size
 * @exception none
 */
int World::setSize(int newSize){
    int oldSize=size;
    size=newSize;
    return oldSize;
}


/**
 * Change culture size
 * @param newCultureCount
 * @return old Culture size
 * @exception none
 */
int World::setCultureCount(int newCultureCount){
    int oldCount=cultureCount;
    cultureCount=newCultureCount;
    return oldCount;
}

/**
 * Change disease length
 * @param newDiseaseLength
 * @return old disease length
 * @exception none
 */
int World::setDiseaseLength(int newDiseaseLength){
    int oldLength= diseaseLength;
    diseaseLength=newDiseaseLength;
    return oldLength;
}


/**
 * Change maximum vision length
 * @param newMaxVision
 * @return old maximum vision length
 * @exception none
 */
int World::setMaxVision(int newMaxVision){
    int oldMax=MaxVision;
    maxVision=newMaxVision;
    return oldMax;
}


/** Change minimum metabolism
 * @param newMinMetabolism
 * @return old minimum metabolism
 * @exception none
 */
int World::setMinMetabolism(int newMinMetabolism){
    int oldMin=MinMetabolism;
    minMetabolism=newMinMetabolism;
    return oldMin;
}


/** Change maximum metabolism
 * @param newMaxMetabolism
 * @return old maximum metabolism
 * @exception none
 */
int World::setMaxMetabolism(int newMaxMetabolism){
    int oldMax=MaxMetabolism;
    maxMetabolism=newMaxMetabolism;
    return oldMax;
}

/** Change sugar growth
 * @param newSugarGrowth
 * @return old sugar growth
 * @exception none
 */
int World::setSugarGrowth(int newSugarGrowth){
    int oldSugar=SugarGrowth;
    sugarGrowth=newSugarGrowth;
    return oldSugar;
}

/** Change spice growth
 * @param newSpiceGrowth
 * @return old spice growth
 * @exception none
 */
int World::setSpiceGrowth(int newSpiceGrowth){
    int oldSpice=SpiceGrowth;
    spiceGrowth=newSpiceGrowth;
    return oldSpice;
}

/** Change minimum age
 * @param newMinAge
 * @return old minimum age
 * @exception none
 */
int World::setMinAge(int newMinAge){
    int oldMin=MinAge;
    minAge=newMinAge;
    return oldMin;
}

/** Change maximum age
 * @param newMaxAge
 * @return old maximum age
 * @exception none
 */
int World::setMaxAge(int newMaxAge){
    int oldMax=MaxAge;
    maxAge=newMaxAge;
    return oldMax;
}


/**
 * change duration
 * @param newDuration
 * @return old duration
 * @exception none
 */
int World::setDuration(int newDuration){
    int oldDuration=duration;
    duration=newDuration;
    return oldDuration;
}

/**
 * change rate
 * @param newRate
 * @return old rate
 * @exception none
 */
int World::setRate(int newRate){
    int oldRate=rate;
    rate=newRate;
    return oldRate;
}

/**
 * change Initial Sugar minimum
 * @param newInitialSugarMin
 * @return old Initial Sugar minimum
 * @exception none
 */
int World::setInitialSugarMin(int newInitialSugarMin){
    int oldMin=initialSugarMin;
    initialSugarMin=newInitialSugarMin;
    return oldMin;
}


/**
 * change Initial Sugar maximum
 * @param newInitialSugarMax
 * @return old Initial Sugar maximum
 * @exception none
 */
int World::setInitialSugarMax(int newInitialSugarMax){
    int oldMax=initialSugarMax;
    initialSugarMax=newInitialSugarMax;
    return oldMax;
}


/**
 * change Initial Spice minimum
 * @param newInitialSpiceMin 
 * @return old Initial Spice minimum
 * @exception none
 */
int World::setInitialSpiceMin(int newInitialSpiceMin){
    int oldMin=initialSpiceMin;
    initialSpiceMin=newInitialSpiceMin;
    return oldMin;
}

/**
 * change Initial Spice maximum
 * @param newInitialSpiceMax
 * @return old Initial Spice maximum
 * @exception none
 */
int World::setInitialSpiceMax(int newInitialSpiceMax){
    int oldMax=initialSpiceMax;
    initialSpiceMax=newInitialSpiceMax;
    return oldMax;
}


/**
 * change winter rate
 * @param newWinterRate
 * @return old Winter Rate
 * @exception none
 */
int World::setWinterRate(int newWinterRate){
    int oldRate=winterRate;
    winterRate=newWinterRate;
    return oldRate;
}


/**
 * change season length
 * @param newSeasonLength
 * @return old season length
 * @exception none
 */
int World::setSeasonLength(int newSeasonLength){
    int oldLength=seasonLength;
    seasonLength=newSeasonLength;
    return oldLength;
}

/**
 * change Production rate
 * @param newProduction
 * @return old Production rate
 * @exception none
 */
int World::setProduction(int newProduction){
    int oldRate=production;
    production=newProduction;
    return oldRate;
}

/**
 * change Concumption Rate
 * @param newConsumption
 * @return old consumption rate
 * @exception none
 */
int World::setConsumption(int newConsumption){
    int oldRate=consumption;
    consumption=newConsumption;
    return oldRate;
}

/**
 * change Combat Limit
 * @param newCombatLimit
 * @return old Combat Limit
 * @exception none
 */
int World::setCombatLimit(int newCombatLimit){
    int oldLimit=combatLimit;
    combatLimit=newCombatLimit;
    return oldLimit;
}

/**
 * change immunity Length
 * @param newImmunityLength
 * @return old immunity length
 * @exception none
 */
int World::setImmunityLength(int newImmunityLength){
    int oldLength=immunityLength;
    immunityLength=newImmunityLength;
    return oldLength;
}

/**
 * change Initial Population Size
 * @param newInitialPopulationSize
 * @return old initial population size
 * @exception none
 */
int World::setInitialPopulationSize(int newInitialPopulationSize){
    int oldSize=initialPopulationSize;
    initialPopulationSize=newInitialPopulationSize;
    return oldSize;
}

/**
 * change winter rate
 * @param newWinterRate
 * @return old Winter Rate
 * @exception none
 */
int World::setPollutionRate(int newPollutionRate){
    pollutionRate=newPollutionRate;
    return pollutionRate;
}

/**
 * change child amount
 * @param newChildAmount
 * @return old child amount
 * @exception none
 */
int World::setChildAmount(int newChildAmount){
    int oldAmt=childAmount;
    childAmount=newChildAmount;
    return oldAmt;
}

/**
 * change number of diseases created for each agent
 * @param newInitialDiseaseCount
 * @return old InitialDiseaseCount
 * @exception none
 */
int World::setInitialDiseaseCount(int newInitialDiseaseCount){
    int oldCount=initialDiseaseCount;
    initialDiseaseCount=newInitialDiseaseCount;
    return oldCount;
}
/**
 * put agent at location *Does NOT delete pointer to old agent!*
 * @param pos :std::pair indices of location 
 * @param newAgent pointer to new agent
 * @return pointer to agent we are replacing (if any)
 * @exception none
 */
Agent* World::setAgent(std::pair<int,int> pos, Agent *newAgent){
    return Lattice[wrap(pos.first)*size+wrap(pos.second)].setAgent(newAgent);
}

/**
 * Kill an agent at location
 * @param pos :std::pair indices of location of agent
 * @return pointer to dead agent (sync will delete pointer)
 * @exception none
 */
Agent* World::killAgent(std::pair<int,int> pos)
{
    if (Lattice[wrap(pos.first)*size+wrap(pos.second)].hasAgent()) {
        return Lattice[wrap(pos.first)*size+wrap(pos.second)].killAgent();
    }
    else
    {
        return nullptr;
    }
}



/**
 * read in config file --comma delimited ints
 * @param configFile :name (incl. path) of configfile
 * @return number of items read
 * @exception none
 */
int World::readIniFile(std::string iniFile)
{//TO DO: get this working!!
    QSettings settings(QString::fromUtf8(iniFile.c_str()), QSettings::IniFormat);
    QString someValue = settings.value("some/config/key", "default value if unset").toString();
    size= settings.value("grid/size","50").toInt();
}


/**
 * read in sugar layout file --comma delimited ints
 * @param configFile :name (incl. path) of configfile
 * @return number of items read
 * @exception none
 */
int World::readConfigFile(std::string configFile)
{
    std::ifstream  data(configFile);
    std::string line;
    int i=0;
    while(std::getline(data,line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            int number=stoi(cell);
            Lattice[i].setMaxSugar(number*2);/*!< -- increased allocation for evolution*/
            Lattice[i].setSugar(number*2);
            ++i;
        }
    }
    return i;
}

/**
 * put string in log file
 * @param msg :message for log file (as string)
 * @return nothing as yet
 * @exception none
 */
int World::log(std::string msg){
    outputLog << msg << std::endl;
    return 1;
}
//****************RULE APPLICATION**************************

/**
 * Add a rule to the list of active rules
 * @param rule
 * @return number of rules  that are active
 * @exception none
 */
int World::addRule(Action* rule){
    activeRules.push_back(rule);
    return (int)activeRules.size();
}

/**
 * apply each active rule in turn
 * @return number of rules applied
 * @exception none
 */
int World::applyRules(){
    int ruleCount=0;
    for(auto rule:activeRules){
        ruleCount+=rule->run(0,0,size);
        if (rule->getStrategy()->needsSync()) sync();
        //sync();
        resetNeighbours();
    }
    return ruleCount;
}

/**
 * Remove all active rules
 * @return number of rules removed
 * @exception none
 */
int World::clearRules(void){
    int ruleCount=activeRules.size();
    activeRules.clear();
    return ruleCount;
}

/**
 * Initialise all active rules
 * @return number of rules active
 * @exception none
 */
int World::initialiseRules(void){
    int ruleCount=0;
    for(int i=0;i<RuleCount;++i){
        if (liveRules[i]==true){
            ++ruleCount;
            addRule(Rules[i]);
        }
    }
    return ruleCount;
}

/**
 * Actives rules based on index
 * @param index rule number
 * @return -1 if rule already active else index
 * @exception none TO DO: check for bounds error
 */
int World::activateRule(int index){
    if (index<0 || index>RuleCount) return -2;
    if (liveRules[index]==true){
        return -1;
    }
    else{
        liveRules[index]=true;
        return index;
    }
}


/**
 * Actives rules based on index
 * @param index rule number
 * @return -1 if rule already inactive else index
 * @exception none TO DO: check for bounds error
 */
int World::deactivateRule(int index){
    if (index<0 || index>RuleCount) return -2;
    if (liveRules[index]==false){
        return -1;
    }
    else{
        liveRules[index]=false;
        return index;
    }
}
