//
// Created by Anatashi on 07.12.2021.
//

#include <fstream>
#include <boost/algorithm/string.hpp>
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

Eigen::MatrixXd CSVTransform::CSVtoEigenMatrixXd(std::vector<std::vector<std::string>>& dataset, int rows, int columns) {
    int i = 0;
    Eigen::MatrixXd matrix;

    if (header_ == true) {
        --rows;
        ++i;
        matrix.resize(rows, columns);
        for (int mat_i = 0; i <= rows; ++i, ++mat_i) {
            for (int j = 0; j < columns; ++j) {
                matrix(mat_i, j) = std::stod(dataset[i][j]);
            }
        }
    } else {
        matrix.resize(rows, columns);
        for (int mat_i = 0; i < rows; ++i, ++mat_i) {
            for (int j = 0; j < columns; ++j) {
                matrix(mat_i, j) = std::stod(dataset[i][j]);
            }
        }
    }

    return matrix.transpose();
}