//
// Created by Andrew Laskin on 1/13/26.
//

#ifndef BACKTESTING_MOVINGAVERAGECROSSOVER_H
#define BACKTESTING_MOVINGAVERAGECROSSOVER_H
#include "util/Indicator.h"
#include "strategy/Strategy.h"
//note to self: position sizing can be implement
//so we can just assume one trade at a time
//and just buying as many shares as we can

struct Portfolio;

class MovingAverageCrossover : public Strategy {
public:
    MovingAverageCrossover(
        double stopLossPercent_,
        double ATRthreshold_,
        int sma = 50,
        int fma = 20,
        int atr = 14
    )
        : indicator(sma, fma, atr)
        , ATRthreshold(ATRthreshold_)
        , stopLossPercent(stopLossPercent_)
    {}
    Signal onBarClose(double close, double high, double low, const Portfolio& portfolio);

private:
    Indicator indicator;



    double ATRthreshold;
    double stopLossPercent;
};
#endif //BACKTESTING_MOVINGAVERAGECROSSOVER_H