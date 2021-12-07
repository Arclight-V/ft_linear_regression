//
// Created by Anatashi on 07.12.2021.
//

#include <fstream>
#include "CSVTransform.h"

std::vector<std::vector<std::string>> CSVTransform::readCSV() {
    std::ifstream file(dataset_);
    std::vector<std::vector<std::string>> dataString;
    std::string line;

    while(std::getline(file, line)) {
        std::vector<std::string> vec_to_add;
        boost::algorithm::split(vec_to_add, line, boost::is_any_of(delimiter_));
        dataString.push_back(vec_to_add);
    }

    file.close();

    return dataString;
}