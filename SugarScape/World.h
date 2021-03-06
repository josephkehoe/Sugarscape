//
//  World.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__World__
#define __SugarScape__World__

#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
//#include <bits/shared_ptr.h>
//#include <omp.h>
#include "Location.h"


typedef std::mt19937 MyRNG;  // the Mersenne Twister with a popular choice of parameters


class Action;
class Strategy;
class NewSweepStrategy;
class LineByLineStrategy;
class RndAsyncStrategy;
class IndependentStrategy;
class ReadDependentStrategy;
class WriteStrategy;
class IterativeWriteStrategy;


/*!  \class  World
 \brief World - singleton that holds everything belonging to sim.
 
 This class holds:
 - The Lattice of locations;
 - All agents
 - All simulation parameters
 - All Rules to be used in simulation
 - Random number generator (*need to have one per thread really*)
 
 Each step is called from here.
 */
class World{
    
    //!
    /*!
     All parameters of simulation world are set here.
     Change to suit your simulation
     */
    static const int DIM=50; /*!< Size of lattice dimensions */
    static const int AGENTCOUNT=400; /*!< Initial number of agents */
    static const int CULTURECOUNT=11;/*!<ODD SIZE REQUIRED 11 mentioned in book! */
    static const int DISEASECOUNT=10;/*!<10 is used in book - but other values also used i.e. 25 */
    static const int MaxAge=100; /*!<Highest lifespan for an agent (100 is default)*/
    static const int MaxVision=6;
    static const int MaxMetabolism=4;
    static const int MinAge=60;/*!<Lowest lifespan for an agent (60 is default)*/
    static const int MinMetabolism=1;
    static const int SugarGrowth=1;
    static const int SpiceGrowth=0;
    static const int Duration=10;
    static const int Rate=3;
    static const int InitialPopulationSize=500;
    static const int InitialSugarMax=100;
    static const int InitialSugarMin=50;
    static const int InitialSpiceMax=25;
    static const int InitialSpiceMin=5;
    static const int WinterRate=8;
    static const int SeasonLength=50;
    static const int Production=2;
    static const int Consumption=2;
    static const int CombatLimit=6;
    static const int IMMUNITYLENGTH=50;/*!<set in book  */
    static const int PollutionRate=2;
    static const int ChildAmount=4;
    static const int DISEASELENGTH =10;/*!<Maximum disease length -- set in book  (10)*/
    static const int INITIALDISEASECOUNT=4;/*!<Number of diseases each agent is created with (4) */
    static const int MinFemaleFertilityStart=12;
    static const int MaxFemaleFertilityStart=15;
    static const int MinMaleFertilityStart=12;
    static const int MaxMaleFertilityStart=15;
    static const int MinFemaleFertilityEnd=90;
    static const int MaxFemaleFertilityEnd=100;

    static const int Growbk=0;
    static const int SeasonalGrowbk=1;
    static const int PollutionForm=2;
    static const int Diffuse=3;
    static const int BasicMovement=4;
    static const int Movement=5;
    static const int ClosestMovement=6;
    static const int StrongestMovement=7;
    static const int Combat=8;
    static const int Culture=9;
    static const int Disease=10;
    static const int Credit=11;
    static const int LoanPayments=12;
    static const int Inheritance=13;
    static const int Trade=14;
    static const int Replacemt=15;
    static const int Reproduction=16;
    static const int Metabolism=17;
    static const int Death=18;
    static const int Garbage=19;
    static const int RuleCount=20;
    
    int step; /*!< Number of steps the simulation has run for */
    int size; /*!< Dimensions of lattice  a size*size matrix of locations*/
    int cultureCount;/*!< Length of bitstring containing culture information */
    int diseaseLength;/*!< Maximum length of disease bitstring */
    int initialDiseaseCount;/*!< Number of diseases an agent is born with */
    int diseaseCount;/*!< Number of possible diseases - all predefined */
    int maxVision; /*!< Maximum extent allowable for any agents vision */
    int minMetabolism, maxMetabolism; /*!< minimum and maximum metabolism rates that any agent may be born with */
    int minSpiceMetabolism, maxSpiceMetabolism; /*!< minimum and maximum metabolism rates that any agent may be born with */
    int sugarGrowth; /*!< Rate at which sugar is replenished by each location during a step */
    int spiceGrowth; /*!< Rate at which spice is replenished by each location during a step */
    int minAge,maxAge; /*!< Minimum and maximum allowable lifespan that can be assigned to any agents*/
    int duration; /*!< Duration of all loan lengths in steps */
    int rate; /*!< Rate of interest applied to loans */
    int initialSugarMin,initialSugarMax; /*!< Range of initial sugar allocation given to agents at beginning of simulation */
    int initialSpiceMin,initialSpiceMax; /*!< Range of initial sugar allocation given to agents at beginning of simulation */
    int winterRate; /*!< Rate that sugar grows back during winter season */
    int seasonLength; /*!< Length of each season (winter and summer) */
    int production;/*!< Amount of pollution generated by gathering of unit of sugar by agent*/
    int consumption;/*!< Amount of pollution generated by consumption of unit of sugar by agent (metabolism)*/
    int combatLimit; /*!< Maximum reward attainable through killing an agent */
    int immunityLength;
    int initialPopulationSize; /*!< Starting population size */
    int pollutionRate; /*!< Number of time periods that pass between each diffusion of pollution */
    int childAmount;
    int initialPopulation;
    int femaleFertilityStart,femaleFertilityEnd;/*!<age range that female agent is fertile for*/
    int maleFertilityStart,maleFertilityEnd;/*!<age range that male agent is fertile for*/
    
    Location *Lattice; /*!< 2D (size by size) Matrix of locations in world  */
    //std::vector<Agent*> population; /*!< Agents in simulation NOT USED */
    std::vector<Action*> activeRules; /*!< Rules we run each time step */
    std::vector<std::vector<bool>*> globalDiseaseList;/*!< All diseases that exist */
    //random Numbers
    MyRNG rng;// keep one instance
    //Log file location
    std::ofstream outputLog;
    //INI file location
    std::ifstream iniFile;
    /*!< Declare all possible strategies here */
    Strategy *baseStrategy;
    NewSweepStrategy *newSweep;
    LineByLineStrategy *lineByLine;
    RndAsyncStrategy *rndAsync;
    IndependentStrategy *independent;
    IterativeWriteStrategy *iterativeWrite;
    ReadDependentStrategy *readDependent;
    WriteStrategy *writeDependent;
    /*!< Place all possible Rules here */
    bool liveRules[RuleCount];
    Action *Rules[RuleCount];
public:
    //Constructor and Destructor
    World(int dimensionSize=0);
    ~World();
    
    
    //Getters
    int getRnd(int,int);
    int getStep(void);
    int getSize(void);
    int getCultureCount(void);
    int getDiseaseLength(void);
    int getMaxVision(void);
    int getMinMetabolism(void);
    int getMaxMetabolism(void);
    int getMinSpiceMetabolism(void);
    int getMaxSpiceMetabolism(void);
    int getSugarGrowth(void);
    int getSpiceGrowth(void);
    int getMinAge(void);
    int getMaxAge(void);
    int getDuration(void);
    int getRate(void);
    int getInitialSugarMin(void);
    int getInitialSugarMax(void);
    int getInitialSpiceMin(void);
    int getInitialSpiceMax(void);
    int getWinterRate(void);
    int getSeasonLength(void);
    int getProduction(void);
    int getConsumption(void);
    int getCombatLimit(void);
    int getImmunityLength(void);
    int getInitialPopulationSize(void);
    int getPollutionRate(void);
    int getChildAmount(void);
    int getFemaleMinFertilityAge(void);
    int getFemaleMaxFertilityAge(void);
    int getMaleMinFertilityAge(void);
    int getMaleMaxFertilityAge(void);
    int getInitialDiseaseCount(void);
    int getMaxDiseaseCount(void);
    
    Agent* getAgent(std::pair<int,int>);
    std::vector<Location*> getNeighbourhood(std::pair<int,int>,int);
    std::vector<Location*> getEmptyNeighbourhood(std::pair<int,int>,int);
    std::vector<Location*> getCombatNeighbourhood(std::pair<int,int>,int);
    std::vector<Agent*> getNeighbours(std::pair<int,int>,int);
    Location* getLattice(void);
    Location* getLocation(std::pair<int, int>);
    std::vector<bool>* getRandomDisease(void);
    
    //Setters
    int incStep();
    int setSize(int);
    int setCultureCount(int);
    int setDiseaseLength(int);
    int setMaxVision(int);
    int setMinMetabolism(int);
    int setMaxMetabolism(int);
    int setSugarGrowth(int);
    int setSpiceGrowth(int);
    int setMinAge(int);
    int setMaxAge(int);
    int setDuration(int);
    int setRate(int);
    int setInitialSugarMin(int);
    int setInitialSugarMax(int);
    int setInitialSpiceMin(int);
    int setInitialSpiceMax(int);
    int setWinterRate(int);
    int setSeasonLength(int);
    int setProduction(int);
    int setConsumption(int);
    int setCombatLimit(int);
    int setImmunityLength(int);
    int setInitialPopulationSize(int);
    int setPollutionRate(int);
    int setChildAmount(int);
    int setInitialDiseaseCount(int);
    Agent* setAgent(std::pair<int,int>,Agent*);
    Agent* killAgent(std::pair<int,int>);
    
    //helpers
    bool init(std::string logFileName="log/output.log",
              std::string configFileName="startup.csv",std::string iniFile="config.ini",
              int vision=1,int metabolism=1);
    int sync(void);
    void sanityCheck(void);
    int wrap(int);
    int getAgentCount(void);
    int getBlueCount(void);
    bool resetNeighbours(void);
    int readIniFile(std::string);
    int readConfigFile(std::string);
    int log(std::string);

    //Rule Application
    int addRule(Action*);
    int applyRules(void);
    int clearRules(void);
    int initialiseRules(void);
    int activateRule(int);
    int deactivateRule(int);
    

};


#endif /* defined(__SugarScape__World__) */
