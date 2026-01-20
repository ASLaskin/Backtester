//
// Created by Andrew Laskin on 1/20/26.
//

#ifndef BACKTESTING_STRATEGY_H
#define BACKTESTING_STRATEGY_H


#include "engine/Engine.h"  //for portfolio
#include "util/Signal.h"

class Strategy {
public:
    virtual ~Strategy() = default;

    virtual Signal onBarClose(
        double close,
        double high,
        double low,
        const Portfolio& portfolio
    ) = 0;
};

#endif //BACKTESTING_STRATEGY_H