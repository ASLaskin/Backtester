#include <iostream>
#include "data/DataFeed.h"
#include "engine/Engine.h"
#include "strategy/MovingAverageCrossover.h"
#include "strategy/MeanReversion.h"
using std::cout;
using std::endl;

int main()
{
    DataFeed data_feed("../testData/AFGhourly.csv");

    // MovingAverageCrossover strategy(0.02, 1.0);
    MeanReversion strategy(20, 2.0, 0.02);

    Engine backtester(data_feed, strategy);

    cout << "Starting Cash Amount: " << backtester.getCash() << endl;
    cout << std::string(10, '-') << endl;

    backtester.run();

    cout << std::string(10, '-') << endl;
    cout << "Sell orders: " << backtester.getSellTradeOrders() << endl;
    cout << "Realized PNL: " << backtester.getRealizedPNL() << endl;
    cout << "Unrealized PNL: " << backtester.getUnrealizedPNL() << endl;
    cout << "Equity: " << backtester.getEquity() << endl;
    cout << "Ended Cash Amount: " << backtester.getCash() << endl;

    return 0;
}