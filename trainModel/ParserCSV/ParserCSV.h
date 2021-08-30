#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>
class ParserCSV {
private:
    ParserCSV();
    std::ifstream csvFile;
    std::vector<double> **arrayNumbers;
public:
    ParserCSV(char *pathToCSV);
    virtual ~ParserCSV();
};


#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//