//
// Created by Andrew Laskin on 1/12/26.
//

#ifndef BACKTESTING_ENGINE_H
#define BACKTESTING_ENGINE_H

class DataFeed;
class Strategy;

enum class OrderType {
    Buy,
    Sell,
    None
};

struct Portfolio {
    double cash;
    bool position;
    double entryPrice;
    double shares;

    double realized_pnl;
    double unrealized_pnl;
    double equity;

    int sellTradeOrders;
};

class Engine{
public:
    explicit Engine(DataFeed& datafeed);

    void run();

    double getRealizedPNL() const {
        return portfolio.realized_pnl;
    }

    double getUnrealizedPNL() const {
        return portfolio.unrealized_pnl;
    }

    double getCash() const {
        return portfolio.cash;
    };

    int getSellTradeOrders() const {
        return portfolio.sellTradeOrders;
    }

    double getEquity() const {
        return portfolio.equity;
    }

private:
    DataFeed& datafeed;
    Portfolio portfolio;

    void updateEquity(double markPrice);

};
#endif