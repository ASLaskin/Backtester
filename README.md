# Project Summary 

A backtesting engine to test trading strategies.

# How to build the program

```bash
mkdir build
cd build
cmake ..
make
./backtesting
```

To run the visualization, create a vertual enviroment, install matplotlib, and then run main.py 


# File Directory / Classes

- Engine - Brain of the program. Continues flow of data,  manages portfolio state, receives orders from the strategy, and also keeps track of PNL and Equity 
- Datafeed - Uses file iterator class to go through csv and returns a bar with Open,high,low,close and other columns
- Indicator - Calculates technical indicators including moving averages (SMA, FMA) and Average True Range (ATR)
- BollingerBands - Calculates Bollinger Bands (upper band, lower band, mean, standard deviation) used for mean reversion strategies
- MovingAverageCrossover - Trading strategy that uses moving average crossovers with volatility filtering
- MeanReversion - Strategy that uses Bollinger Bands to identify overbought/oversold conditions and execute mean reversion trades with stop-loss protection

# Moving Average Crossover with Volatility filtering 
<details>

<summary>Dropdown</summary>
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

</details>

# Mean Reversion with Bollinger Bands  
<details>

<summary>Dropdown</summary>

This strategy is based on the assumption that price deviations from a rolling mean are temporary and will revert.

It uses Bollinger Bands, which is:
- A moving average (middle band)  
- An upper band = mean + N × standard deviation  
- A lower band = mean − N × standard deviation  

* Buy Signal when price closes below the Lower Bollinger Band  
* Sell Signal when price closes back above the Middle Band (mean)  
* Sell Signal when stoploss is hit  

## Pros
* High win rate in range bound markets    
* Naturally complementary to trend following strategies  

## Cons
* Performs poorly during strong trending markets  
* Susceptible to rare but large drawdowns  
* Contrarian bias (fades momentum)  

## Optimize
* Add volatility regime filters (e.g., ATR contraction filter)  
* Add trend filter (e.g., disable trades when ADX is high)   

</details>

# Moving Forward 

Id like to add another strategy, work on position sizing, and work with other timeframes
