#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>

template<typename T>
class ParserCSV {
private:
    ParserCSV() {};
    std::ifstream csvFile;
    std::vector<T> **arrayNumbers;
public:
    ParserCSV(const char *pathToCSV) : csvFile(pathToCSV), arrayNumbers(nullptr) {
        if (csvFile.is_open()) {
            std::vector<std::string> lines;
            std::string line;
            while (std::getline(csvFile, line)) {
                lines.push_back(line);
            }
            arrayNumbers = new std::vector<T>* [lines.size() - 1];
            std::vector<T> **tmp = arrayNumbers;
            for (size_t i = 1; i < lines.size(); ++i) {
                (*tmp) = new std::vector<T>;
                (*tmp)->push_back(std::stod(lines[i]));
                std::string str = lines[i].substr(lines[i].find(',') + 1, lines[i].size());
                (*tmp)->push_back(std::stod(lines[i].substr(lines[i].find(',') + 1, lines[i].size())));
                ++(*tmp);
            }
        }
    };
    virtual ~ParserCSV() {};
};


#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//