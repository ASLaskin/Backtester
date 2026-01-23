//
// Created by Andrew Laskin on 1/12/26.
//
#include <iostream>
#include "engine/Engine.h"
#include "data/DataFeed.h"
#include "data/FileWriter.h"
#include "strategy/util/Signal.h"
#include "strategy/Strategy.h"

Engine::Engine(DataFeed& datafeed_, Strategy& strategy_)
    : datafeed(datafeed_)
    , strategy(strategy_)
    , portfolio{
        100000.0,  //cash
        false,     //position
        0.0,       //entryprice
        0.0,       //shares
        0.0,       //realized_pnl
        0.0,       //unrealized_pnl
        0.0,       //equity
        0          //sellTradeOrders
    }
{}


void Engine::run(){
    auto orderOnOpen = OrderType::None;
    FileWriter file("../output.txt");

    while (datafeed.next()){
        const Bar& bar = datafeed.getBar();

        file.writeLine(std::to_string(bar.close) + "," + std::to_string(bar.volume));
        if (orderOnOpen == OrderType::Buy) {
            portfolio.entryPrice = bar.open;
            portfolio.position = true;
            portfolio.shares = portfolio.cash / bar.open;
            portfolio.cash = 0.0;
            orderOnOpen = OrderType::None;
            file.writeLine("Buy");
            std::cout << "Buy " << portfolio.shares << " @ " << portfolio.entryPrice << std::endl;
        }
        else if (orderOnOpen == OrderType::Sell) {
            double exit_price = bar.open;
            double pnl = (exit_price - portfolio.entryPrice) * portfolio.shares;

            portfolio.cash = portfolio.shares * exit_price;
            portfolio.realized_pnl += pnl;

            portfolio.shares = 0.0;
            portfolio.position = false;

            portfolio.sellTradeOrders += 1;
            file.writeLine("Sell");
            std::cout << "Sell @" << exit_price << std::endl;
            orderOnOpen = OrderType::None;
        }

        Signal signal = strategy.onBarClose(
            bar.close,
            bar.high,
            bar.low,
            portfolio
        );

        if (signal == Signal::Buy && !portfolio.position ) {
            orderOnOpen = OrderType::Buy;
        }
        else if (signal == Signal::Sell && portfolio.position) {
            orderOnOpen = OrderType::Sell;
        }

        updateEquity(bar.close);
    }
}

void Engine::updateEquity(double markPrice) {
    if (portfolio.position) {
        portfolio.unrealized_pnl = (markPrice - portfolio.entryPrice) * portfolio.shares;

        portfolio.equity = portfolio.cash + portfolio.shares * markPrice;
    } else {
        portfolio.unrealized_pnl = 0.0;
        portfolio.equity = portfolio.cash;
    }
}

