#include "ParserCSV.h"

ParserCSV::ParserCSV() {}

ParserCSV::ParserCSV(char *pathToCSV) : csvFile(pathToCSV), arrayNumbers(nullptr) {
    if (csvFile.is_open()) {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(csvFile, line)) {
            lines.push_back(line);
        }
        arrayNumbers = new std::vector<double>* [lines.size() - 1];
        std::vector<double> **tmp = arrayNumbers;
        for (size_t i = 1; i < lines.size(); ++i) {
            (*tmp) = new std::vector<double>;
            (*tmp)->push_back(std::stod(lines[i]));
            std::string str = lines[i].substr(lines[i].find(',') + 1, lines[i].size());
            (*tmp)->push_back(std::stod(lines[i].substr(lines[i].find(',') + 1, lines[i].size())));
            ++(*tmp);
        }
    }
}

ParserCSV::~ParserCSV() {
//    for(std::vector<double> **tmp = arrayNumbers; *tmp; ++(*tmp)) {
//        delete *tmp;
//    }
//    delete arrayNumbers;
}

//
// Created by Arclight Natashia on 8/27/21.
//