//
//  WriteAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "WriteAction.h"
#include "Strategy.h"

/**
 * Constructor - passes World pointer to parent constructor
 * @param sim :Pointer to World
 * @param theStrategy :pointer to preferred Strategy
 * @return none
 * @exception none
 */
WriteAction::WriteAction(World* sim, Strategy* theStrategy):Action(sim,theStrategy){
    
}
WriteAction::~WriteAction(void){
    
}


/**
 * run - Applies action to every location in lattice within parameter limits
 * @param startX :Starting X position of tile we are executing
 * @param startY :starting Y position of tile
 * @param size :dimensions of our tile (we assume square tiles)
 * @see Write-Dependent Algorithm
 * @return true
 * @exception none
 */
//bool WriteAction::run(int startX, int startY, int size){
////    Location* Lattice=sim->getLattice();
////    int remaining=0;
////    std::vector<group*>  ExclusiveGroups,FailedGroups;
////    //calculate number of entities that need to take part in this actions
////    remaining=participantCount(startX, startY, size);
////    while (remaining>0) {//loop until all active participants are in groups
////        std::vector<group*> proposedGroups;
////        //Part One: Form group proposals
////#pragma omp parallel for
////        for (int i=startX; i<startX+size; ++i ) {
////            for (int k=startY; k<startY+size; ++k) {
////                if (Lattice[i*sim->getSize()+k].isDone()==false){
////                    group *grp = formGroup(&Lattice[i*sim->getSize()+k]);
////                    if (grp!=nullptr) {/*!< do not add nullptrs as they will interfere with sorting */
////#pragma omp critical(pushBack)
////                        {
////                        proposedGroups.push_back(grp);
////                        }
////                    }
////                }
////            }
////        }
////        //Part Two: Sort proposed groups
////        std::sort(proposedGroups.begin(), proposedGroups.end(), group::compare);
////        //Part Three: Find Exclusive Groups
////        for(auto grp:proposedGroups){
////            bool exclusive=true;
////            std::vector<Location*> members=grp->getMembers();
////            for(auto loc:members){//any agents in group already taken?
////                if (loc->isDone()) {
////                    exclusive=false;
////                }
////            }
////            if (grp->getPrimeMover()->isDone()) {
////                exclusive=false;
////            }
////            //all agents in group are free then
////            // add group to exclusiveGroups and mark each location as done
////            if (exclusive) {//all agents in group are free!
////                ExclusiveGroups.push_back(grp);
////                grp->getPrimeMover()->markDone();
////                for(auto loc:members){
////                    loc->markDone();
////                }
////                remaining=remaining-grp->getActiveParticipants();//reduce number of entities left to place
////            }else{//group is not exclusive store it for deletion!
////                FailedGroups.push_back(grp);
////            }
////        }
////    }//While
////    //Exclusive Groups all formed here. Apply actions
////#pragma omp parallel for
////    for(int i=0;i<ExclusiveGroups.size();++i){
////        executeAction(ExclusiveGroups[i]->getPrimeMover(),ExclusiveGroups[i]);
////    }
//////    for(auto grp:ExclusiveGroups){
//////        executeAction(grp->getPrimeMover(),grp);
//////    }
////    //delete groups
////#pragma omp parallel for
////    for(int i=0;i<ExclusiveGroups.size();++i){
////        delete ExclusiveGroups[i];
////    }
////#pragma omp parallel for
////    for(int i=0;i<FailedGroups.size();++i){
////        delete FailedGroups[i];
////    }
//////    for(auto grp:ExclusiveGroups){
//////         delete grp;
//////    }
//////    for(auto grp:FailedGroups){
//////        delete grp;
//////    }
////    return true;
//    return theStrategy->run(startX,startY,size,this);
//}


/**
 * Concurrent version of run
 * @see Concurrent Write-Dependent Algorithm
 * @return true
 * @exception none
 */
//bool WriteAction::concurrentRun(void){
////    int sectionSize=sim->getMaxVision();
////    /*!< construct tile set - tile contains 9 sections - 3 each side*/
////    int tileDim=3*sectionSize;
////    int tileNum=sim->getSize()/tileDim;/*!< Assume size%tileDim==0 */
////    if (sim->getSize()%tileDim!=0) {
////        std::cout << "TILE SIZE ERROR"<<std::endl;
////    }
////    int totalTiles=tileNum*tileNum;
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim,(i%tileNum)*tileDim,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim,(i%tileNum)*tileDim+sectionSize,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim,(i%tileNum)*tileDim+2*sectionSize,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize,(i%tileNum)*tileDim,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize,(i%tileNum)*tileDim+sectionSize,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize,(i%tileNum)*tileDim+2*sectionSize,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize*2,(i%tileNum)*tileDim,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize*2,(i%tileNum)*tileDim+sectionSize,sectionSize);
////    }
////#pragma omp parallel for
////    for (int i=0; i<totalTiles; ++i) {
////        run((i/tileNum)*tileDim+sectionSize*2,(i%tileNum)*tileDim+2*sectionSize,sectionSize);
////    }
////    return true;
//    return theStrategy->concurrentRun(this);
//}


/**
 Calculate the number of active participants in this action on the grid
 Default is number of agents - assume they are all active
 @param startX :start Index for row
 @param startY :start index for column
 @param dimSize :Dimensions of grid size
 @returns number of agents in this grid
 @exception none
 */
//int WriteAction::participantCount(int startX, int startY, int dimSize)
//{
//    int pcount=0;
//#pragma omp parallel for
//    for (int i=startX; i<startX+dimSize; ++i) {
//        for (int k=startY; k<startY+dimSize; ++k) {
//            if (sim->getAgent(std::pair<int,int>(i, k)) != nullptr && sim->getAgent(std::pair<int,int>(i, k))->isDone()==false) {
//                ++pcount;
//            }
//        }
//    }
//    return pcount;
//}


/**
 pick index from list of available locations
 
 Picks randomly, May be required to help form group reimplement if you want
 a more intelligent picking behaviour e.g. pick best/nearest/weakest neighbour
 
 @param possibleDestinations :vector of locations we can move to
 @returns index of chosen location in vector
 @exception none
 */
//int WriteAction::pickIndex(std::vector<Location*> possibleDestinations)
//{
//    return sim->getRnd(0,(int)possibleDestinations.size()-1);//pick random location
//}
