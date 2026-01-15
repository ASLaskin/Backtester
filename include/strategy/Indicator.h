//
// Created by Andrew Laskin on 1/13/26.
//

#ifndef BACKTESTING_INDICATOR_H
#define BACKTESTING_INDICATOR_H
#include <deque>

//strategy owns indicator and indicator has access to bar
//indicator will give back the SMA, FMA, ATR etc and then strategy will
//return what signal it should send to the engine

// the strategy i want to implement
// Moving Average Crossover with Volatility Filter

class Indicator{
public:
   Indicator(const int sma_period = 50, const int fma_period = 20, const int atr_period = 14)
      : SMATotal(0.0)
      , FMATotal(0.0)
      , TRTotal(0.0)
      , SMAperiod(sma_period)
      , FMAperiod(fma_period)
      , ATRPeriod(atr_period)
      , prevClose(0.0)
      {};

   bool ready() const ;

   void onBarClose(const double &close,const double &high,const double &low);

   double getSMA() const {
      return SMATotal / SMAperiod;
   }

   double getFMA() const {
      return FMATotal / FMAperiod;
   }

   double getATR()const {
      if (TRvalues.empty()) return 0.0;
      return TRTotal / TRvalues.size();
   };



private:
   //Slow and Fast Moving Average
   std::deque<double> SMAvalues;
   std::deque<double> FMAvalues;
   std::deque<double> TRvalues;

   //this is before we divide by # periods
   double SMATotal;
   double FMATotal;
   double TRTotal;

   //this is how many periods we want to occur for each
   int SMAperiod;
   int FMAperiod;
   int ATRPeriod;

   bool firstBar = true;
   double prevClose;
};
#endif //BACKTESTING_INDICATOR_H