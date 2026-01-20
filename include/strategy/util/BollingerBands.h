//
// Created by Andrew Laskin on 1/20/26.
//

#ifndef BACKTESTING_BOLLINGERBANDS_H
#define BACKTESTING_BOLLINGERBANDS_H
#include <deque>

class BollingerBands {
public:
    BollingerBands(int period_, double stddevMultiplier_)
        : period(period_)
        , stddevMultiplier(stddevMultiplier_)
        , sum(0.0)
        , sumSq(0.0)
    {}

    void onBarClose(double close) {
        window.push_back(close);
        sum += close;
        sumSq += close * close;

        if (window.size() > period) {
            double old = window.front();
            window.pop_front();
            sum -= old;
            sumSq -= old * old;
        }
    }

    bool ready() const {
        return window.size() == period;
    }

    double mean() const {
        return sum / period;
    }

    double stddev() const {
        double m = mean();
        double variance = (sumSq / period) - (m * m);
        return std::sqrt(std::max(variance, 0.0));
    }

    double upper() const {
        return mean() + stddevMultiplier * stddev();
    }

    double lower() const {
        return mean() - stddevMultiplier * stddev();
    }

private:
    int period;
    double stddevMultiplier;

    std::deque<double> window;
    double sum;
    double sumSq;
};

#endif //BACKTESTING_BOLLINGERBANDS_H