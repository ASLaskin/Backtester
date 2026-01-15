#include <iostream>
#include "data/DataFeed.h"
#include "engine/Engine.h"

using std::cout;
using std::endl;

int main()
{
    DataFeed data_feed("../testData/AFGhourly.csv");
    Engine backtester(data_feed);

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