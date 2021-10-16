#include "ParserCSV/ParserCSV.h"
#include <Eigen/Core>
#include <Eigen/Dense>

int main() {
    ParserCSV<double> parserCsv("../../resources/data.csv", ',');

    std::vector<double> tmp = parserCsv.getRow(0);

    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

