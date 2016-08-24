//
// Created by joseph on 24/08/16.
//

#ifndef SUGARSCAPE_UNIFORMCHOICE_H
#define SUGARSCAPE_UNIFORMCHOICE_H


#include <netinet/in.h>
#include "Strategy.h"

class UniformChoice : public Strategy{
    int *ordering;
    int size;
protected:
    bool shuffle();/*!< Chooses the random ordering */
public:
    UniformChoice(World *sim);
    virtual ~UniformChoice();
    virtual bool run(int, int , int ,Action*);/*!< Standard run algorithm handling concurrency */
    virtual bool needsSync(void); /*!< Do we need to sync world after strategy application? */
};


#endif //SUGARSCAPE_UNIFORMCHOICE_H
