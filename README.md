# Project Summary 

A backtesting engine to test trading strategies.

# How to build the program

mkdir build 
cd build 
cmake ..
make
./backtesting

# File Directory / Classes

Engine - Brain of the program. Continues flow of data,  manages portfolio state, receives orders from the strategy, and also keeps track of PNL and Equity 
Datafeed - Uses file iterator class to go through csv and returns a bar with Open,high,low,close and other columns
Indicator - Keeps track of moving averages (MA) and average true range (ATR). Pretty much what the strategy will be using to make a decision
MovingAverageCrossover - Strategy class that returns either Buy,Sell,Hold order read more on strategy 

# Moving Average Crossover with Volatility filtering 

The strategy I implemented uses a Slow and Fast MA (20 & 50 periods respectively) but other versions may use more MA like slow,medium,fast.

* Buy Signal when the Fast MA is above the Slow MA
* Sell Signal when Fast MA is below the Slow MA
* Sell Signal when stoploss is hit

Only send the signal once ATR exceeds a certain user defined treshold. 

## Pros
* Bidirectional trading
* Using multiple MA's captures overall trend well

## Cons
* Over reliance on technical indicators ( does not account for major events, news, etc. )
* Moving Averages are inherently lagging indicators

## Optimize
* Add another moving average
* Currently bidirectional trading isn't implemented
* Position Management

# Moving Forward 

Id like to add another strategy, work on position sizing, and work with other timeframes
