//
// Created by Anatashi on 07.12.2021.
//

#ifndef FT_LINEAR_REGRESSION_CSVTRANSFORM_H
#define FT_LINEAR_REGRESSION_CSVTRANSFORM_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

class CSVTransform {
    std::string dataset_;
    std::string delimiter_;
    bool header_;

public:
    CSVTransform(const std::string& csv_file_name, const std::string& delimiter, const bool header) : dataset_(csv_file_name),
                                                                                  delimiter_(delimiter),
                                                                                  header_(header)
    {}
    CSVTransform(const CSVTransform& rhs) = delete;
    ~CSVTransform() = default;
    CSVTransform& operator=(const CSVTransform& rhs) = delete;

    std::vector<std::vector<std::string>> readCSV();
};


#endif //FT_LINEAR_REGRESSION_CSVTRANSFORM_H
