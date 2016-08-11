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
//#include <omp.h>
#include "Location.h"


typedef std::mt19937 MyRNG;  // the Mersenne Twister with a popular choice of parameters
  


class Action;


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
    static const int AGENTCOUNT=500; /*!< Initial number of agents */
    static const int CultureCount=11;/*!<ODD SIZE REQUIRED 11 mentioned in book! */
    static const int MaxAge=100;
    static const int MaxVision=6;
    static const int MaxMetabolism=4;
    static const int MinAge=60;
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
    static const int ImmunityLength=30;
    static const int PollutionRate=2;
    static const int ChildAmount=4;
    static const int DiseaseLength=5;
    static const int MinFemaleFertilityStart=12;
    static const int MaxFemaleFertilityStart=15;
    static const int MinMaleFertilityStart=12;
    static const int MaxMaleFertilityStart=15;
    static const int MinFemaleFertilityEnd=90;
    static const int MaxFemaleFertilityEnd=100;

    
    int step; /*!< Number of steps the simulation has run for */
    int size; /*!< Dimensions of lattice  a size*size matrix of locations*/
    int cultureCount;/*!< Length of bitstring containing culture information */
    int diseaseLength;/*!< Length of disease bitstring assuming all diseases are same length */
    int maxVision; /*!< Maximum extent allowable for any agents vision */
    int minMetabolism, maxMetabolism; /*!< minimum and maximum metabolism rates that any agent may be born with */
    int minSpiceMetabolism, maxSpiceMetabolism; /*!< minimum and maximum metabolism rates that any agent may be born with */
    int sugarGrowth; /*!< Rate at which sugar is replenished by each location during a step */
    int spiceGrowth; /*!< Rate at which sugar is replenished by each location during a step */
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
    
    //random Numbers
    MyRNG rng;// keep one instance
    //Log file location
    std::ofstream outputLog;
    
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
    
    Agent* getAgent(std::pair<int,int>);
    std::vector<Location*> getNeighbourhood(std::pair<int,int>,int);
    std::vector<Location*> getEmptyNeighbourhood(std::pair<int,int>,int);
    std::vector<Location*> getCombatNeighbourhood(std::pair<int,int>,int);
    std::vector<Agent*> getNeighbours(std::pair<int,int>,int);
    Location* getLattice(void);
    Location* getLocation(std::pair<int, int>);
    
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
    Agent* setAgent(std::pair<int,int>,Agent*);
    Agent* killAgent(std::pair<int,int>);
    
    //helpers
    bool init(std::string logFileName="log/output.log",int vision=1,int metabolism=1);
    int sync(void);
    void sanityCheck(void);
    int wrap(int);
    int getAgentCount(void);
    int getBlueCount(void);
    bool resetNeighbours(void);
    int readConfigFile(std::string);
    int log(std::string);

    //Rule Application
    int addRule(Action*);
    int applyRules(void);
    

};


#endif /* defined(__SugarScape__World__) */
