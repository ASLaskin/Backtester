//
// Created by Andrew Laskin on 1/13/26.
//

#include "strategy/Indicator.h"

void Indicator::onBarClose(const double &close,const double &high,const double &low) {
    SMATotal += close;
    SMAvalues.push_back(close);
    if (SMAvalues.size() > SMAperiod) {
        SMATotal -= SMAvalues.front();
        SMAvalues.pop_front();
    }

    FMATotal += close;
    FMAvalues.push_back(close);
    if (FMAvalues.size() > FMAperiod) {
        FMATotal -= FMAvalues.front();
        FMAvalues.pop_front();
    }

    if (!firstBar) {
        const double tr = std::max({high - low, std::abs(high - prevClose), std::abs(low - prevClose)});
        TRTotal += tr;
        TRvalues.push_back(tr);
        if (TRvalues.size() > ATRPeriod) {
            TRTotal -= TRvalues.front();
            TRvalues.pop_front();
        }
    }
    prevClose = close;
    firstBar = false;
}

bool Indicator::ready() const {
    return SMAvalues.size() >= SMAperiod && FMAvalues.size() >= FMAperiod && TRvalues.size() >= ATRPeriod;;
}