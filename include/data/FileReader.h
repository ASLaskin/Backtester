//
// Created by Andrew Laskin on 1/10/26.
//

#ifndef BACKTESTING_FILEREADER_H
#define BACKTESTING_FILEREADER_H
#include <iostream>
#include <fstream>
#include <string>

class FileReader
{
    std::ifstream file;
    std::string line;

public:
    explicit FileReader(const std::string& fileName_) : file(fileName_){
        if (!file.is_open())
            throw std::runtime_error("file failed to open");

    }

    bool next(std::string& output){
        return static_cast<bool>(std::getline(file,output));
    }
};
#endif