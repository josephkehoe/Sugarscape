//
//  group.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "group.h"



//*****************************CONSTRUCTORS*****************************
group::group(void):
    rank(0),size(0){
    
}
//*****************************GETTERS*****************************
/**
 Returns the ranking of a group, for sorting
 @returns rank
 @exception void
 */
int group::getRank(void){
    return rank;
}
/**
 Returns the list (std::vector<Location*>) of members in the group
 @returns members
 @exception void
 */
std::vector<Location*> group::getMembers(void){
    return members;
}
/**
 Returns the number of elements in the group
 @returns size
 @exception void
 */
int group::getSize(void){
    return size;
}


//*****************************SETTERS*****************************

/**
 Adds a new location to a group
 @param location pointer
 @returns number of locations now in group
 @exception void
 */
int group::push_back(Location* location){
    members.push_back(location);
    return ++size;
}
/**
 Attaches a rank to a group. Used for sorting groups by importance for collision resolution
 @param newRank :Integer value equalling new ranking score
 @returns new ranking score
 @exception void
 */
int group::setRank(int newRank){
    return rank=newRank;
}

//*****************************HELPERS*****************************

/**
 Compares two groups and returns true if the first group has a lower rank than the second
 @param first :A pointer to a group
 @param second :A pointer to a group
 @returns true if first has lower rank else false
 @exception void
 */
bool group::compare(group *first, group *second){
    return first->getRank()<second->getRank();
}
