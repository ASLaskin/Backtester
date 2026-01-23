//
// Created by Andrew Laskin on 1/22/26.
//

#ifndef BACKTESTING_FILEWRITER_H
#define BACKTESTING_FILEWRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class FileWriter {
  std::ofstream file;

public:
  explicit FileWriter(const std::string& fileName_)
    : file(fileName_, std::ios::out)
{

    if (!file.is_open())
      throw std::runtime_error("file failed to open for writing");
}

  void writeLine(const std::string& line) {
    file << line << std::endl;
    if (!file) {
      throw std::runtime_error("file failed to open for writing");
    }
  }

};
#endif //BACKTESTING_FILEWRITER_H