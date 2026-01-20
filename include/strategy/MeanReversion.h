//
// Created by Andrew Laskin on 1/20/26.
//

#ifndef BACKTESTING_MEANREVERSION_H
#define BACKTESTING_MEANREVERSION_H

#include "strategy/Strategy.h"
#include "strategy/util/BollingerBands.h"

class MeanReversion : public Strategy {
public:
    MeanReversion(
        int period = 20,
        double stddevMultiplier = 2.0,
        double stopLossPercent_ = 0.02
    )
        : bands(period, stddevMultiplier)
        , stopLossPercent(stopLossPercent_)
    {}

    Signal onBarClose(
        double close,
        double high,
        double low,
        const Portfolio& portfolio
    ) override;

private:
    BollingerBands bands;
    double stopLossPercent;
};


#endif //BACKTESTING_MEANREVERSION_H