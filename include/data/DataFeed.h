//
// Created by Andrew Laskin on 1/10/26.
//

#ifndef BACKTESTING_DATAFEED_H
#define BACKTESTING_DATAFEED_H

#include <sstream>
#include "FileReader.h"
#include <vector>

struct Bar{
    std::string timestamp;
    double open;
    double high;
    double low;
    double close;
    double adjclose;
    double volume;
};

// the point of this class is to interpret what we get from the
// cvs file and then return a bar
class DataFeed{
public:
    explicit DataFeed(const std::string& fileName_, bool skipHeader_ = true)
    : reader(fileName_)
    {
        if (skipHeader_) {
            std::string dummy;
            reader.next(dummy);
        }
    };

    bool next(){
        std::string line;
        if (reader.next(line)){
            std::istringstream ss(line);
            std::vector<std::string> tokens;
            std::string token;

            while (std::getline(ss, token, ',')){
                tokens.push_back(token);
            }

            try{
                currentBar.timestamp = tokens[0];;
                currentBar.open      = std::stod(tokens[1]);
                currentBar.high      = std::stod(tokens[2]);
                currentBar.low       = std::stod(tokens[3]);
                currentBar.close     = std::stod(tokens[4]);
                currentBar.adjclose  = std::stod(tokens[5]);
                currentBar.volume    = std::stod(tokens[6]);
            }catch (std::runtime_error& e){
                std::cerr << "CSV mismatch to data in Bar";
            }
            return true;
        }
        return false;
    }

    const Bar& getBar() const {return currentBar;}


private:
    FileReader reader;
    Bar currentBar;

};
#endif