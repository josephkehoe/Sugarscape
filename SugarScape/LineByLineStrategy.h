//
// Created by joseph on 30/05/16.
//

#ifndef SUGARSCAPE_LINEBYLINESTRATEGY_H
#define SUGARSCAPE_LINEBYLINESTRATEGY_H
#include "Strategy.h"

/*!  \class  LineByLineStrategy
 \brief Asynchronous updating in order of location

Ordering is based on agent position.  It does each agent in order of location in row then column
 That is, Do agents starting from first row left to right, then next row from left to right.
 Continue until end of lattice is reached. Location[0,0] is checked first then [0,1],[0,2]...
 */

class LineByLineStrategy :public Strategy{

public:
    LineByLineStrategy(World*);
    virtual bool run(int, int , int ,Action*); /*!< Standard run algorithm handling concurrency */
    virtual bool needsSync(void); /*!< Do we need to sync world after strategy application? */
};


#endif //SUGARSCAPE_LINEBYLINESTRATEGY_H
