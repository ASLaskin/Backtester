//
// Created by Andrew Laskin on 1/14/26.
//

#include "strategy/MovingAverageCrossover.h"
//I should have made a seperate portfolio class/file so this looks cleaner
#include "engine/Engine.h"
Signal MovingAverageCrossover::onBarClose(
    double close,
    double high,
    double low,
    const Portfolio& portfolio
) {
    indicator.onBarClose(close, high, low);

    if (!indicator.ready())
        return Signal::Hold;

    double fma = indicator.getFMA();
    double sma = indicator.getSMA();
    double atr = indicator.getATR();

    //volatility filter
    if (atr < ATRthreshold)
        return Signal::Hold;

    if (!portfolio.position && fma > sma) {
        return Signal::Buy;
    }

    //stop loss
    if (portfolio.position) {
        double stopPrice = portfolio.entryPrice * (1.0 - stopLossPercent);
        if (close <= stopPrice) {
            return Signal::Sell;
        }
    }

    if (portfolio.position && fma < sma) {
        return Signal::Sell;
    }

    return Signal::Hold;
}

