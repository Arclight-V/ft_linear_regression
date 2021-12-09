#include "CSVTransform/CSVTransform.h"
#include "ft_linear_regression/ft_linear_regression.h"
#include <iostream>
#include <fstream>
#include <Eigen/Geometry>

namespace csv_parameters {
    std::string kCSVFileName = "../../resources/data.csv";
    std::string kDelimiter = ",";
    constexpr bool kHeader = true;
} // csv_parameters

#if defined(PRINT_MODE)

void printVectorXd(const char* const name, const Eigen::VectorXd& vectorXd) {
        std::cout << "VectorXd " << name << "\n";

        auto *begin = vectorXd.data();
        auto *end = vectorXd.data() + vectorXd.size();
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << "\n\n";
}

#endif

int main() {

    CSVTransform csvTransform(csv_parameters::kCSVFileName,
                              csv_parameters::kDelimiter,
                              csv_parameters::kHeader);

    std::vector<std::vector<std::string>> dataset(csvTransform.readCSV());

    Eigen::MatrixXd dataMatrix = csvTransform.CSVtoEigenMatrixXd(dataset,
                                                                 dataset.size(),
                                                                 dataset[0].size());

    /*
     * X -  значения фактора (регрессора) она же независимоя переменная или предикат
     * y -  фактическое значение целевой переменной при этом регрессоре она же зависимая переменная
     *      или переменная отклика
     */
    Eigen::VectorXd X(dataMatrix.row(0));
    Eigen::VectorXd y(dataMatrix.row(1));
//
//    double SS_tot = 0.0;
//    {
//        auto *begin = y.data();
//        auto *end = y.data() + y.size();
//        for (; begin != end; ++begin) {
//            SS_tot += std::pow(*begin - y.mean(), 2);
//        }
//        SS_tot /= y.size();
//    }


    ft_linear_regression linearRegression;

#if defined(SUBJECT)
    linearRegression.fit_subject(X, y);
#else
    linearRegression.fit(dataMatrix);
#endif

    std::cout << "intercept (tetha0): " << linearRegression.getIntercept() << "\n"
              << "slope     (tetha1): " << linearRegression.getSlope() << '\n';


#if defined(PRINT_MODE)

    printVectorXd("X", X);
    printVectorXd("y", y);

#endif

    std::fstream file_to_safe("../../resources/coefficient.txt");

    file_to_safe << std::fixed << linearRegression.getIntercept() << " " << linearRegression.getSlope();
    file_to_safe.close();

    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

