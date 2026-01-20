//
// Created by Andrew Laskin on 1/20/26.
//

#include "strategy/MeanReversion.h"

Signal MeanReversion::onBarClose(
    double close,
    double high,
    double low,
    const Portfolio& portfolio
) {
    bands.onBarClose(close);

    if (!bands.ready())
        return Signal::Hold;

    double upper = bands.upper();
    double lower = bands.lower();
    double mean  = bands.mean();

    if (!portfolio.position && close <= lower) {
        return Signal::Buy;
    }

    if (portfolio.position) {
        double stopPrice = portfolio.entryPrice * (1.0 - stopLossPercent);
        if (close <= stopPrice) {
            return Signal::Sell;
        }
    }

    if (portfolio.position && close >= mean) {
        return Signal::Sell;
    }

    return Signal::Hold;
}

