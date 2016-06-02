//
// Created by joseph on 03/03/16.
//

#ifndef SUGARSCAPE_RNDASYNCSTRATEGY_H
#define SUGARSCAPE_RNDASYNCSTRATEGY_H


#include <netinet/in.h>
#include "Strategy.h"


/*!  \class  RndAsyncStrategy
 \brief Asynchronous updating in random order

This assumes a random ordering is chosen once at initialisation.
 The chosen order is then used from then onwards
 */
class RndAsyncStrategy : public Strategy{
    int *ordering;
    int size;
protected:
    bool shuffle();/*!< Chooses the random ordering */
public:
    RndAsyncStrategy(World *sim);
    virtual ~RndAsyncStrategy();
    virtual bool run(int, int , int ,Action*);/*!< Standard run algorithm handling concurrency */
    virtual bool needsSync(void); /*!< Do we need to sync world after strategy application? */
};



#endif //SUGARSCAPE_RNDASYNCSTRATEGY_H
