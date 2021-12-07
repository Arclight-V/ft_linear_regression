//
// Created by Anatashi on 07.12.2021.
//

#ifndef FT_LINEAR_REGRESSION_CSVTRANSFORM_H
#define FT_LINEAR_REGRESSION_CSVTRANSFORM_H

#include <iostream>
#include <vector>

//using std::vector<std::vector<std::string>> = TwoDVectorString;

class CSVTransform {
    std::string csv_file_name_;
    std::string delimiter_;
    bool header_;

public:
    CSVTransform(const std::string& csv_file_name, const std::string& delimiter, const bool header) : csv_file_name_(csv_file_name),
                                                                                  delimiter_(delimiter),
                                                                                  header_(header)
    {}

};


#endif //FT_LINEAR_REGRESSION_CSVTRANSFORM_H
