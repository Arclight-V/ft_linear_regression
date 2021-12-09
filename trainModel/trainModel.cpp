#include "CSVTransform/CSVTransform.h"
#include <iostream>
#include <fstream>
#include <Eigen/Geometry>

namespace csv_parameters {
    std::string kCSVFileName = "../../resources/data.csv";
    std::string kDelimiter = ",";
    constexpr bool kHeader = true;
} // csv_parameters

#if defined(MANUAL)
// the sum of the multiplication of elements
double sumMultiplication(const Eigen::MatrixXd &matrixXd) {
    int rows = matrixXd.rows();
    int columns = matrixXd.cols();
    double sum = 0.0;
    double multiplicationLine = 0.0;

    const double **arrayPtr = new const double *[columns];
    const double **tmp = arrayPtr;
    int shift = 0;
    for (; shift < matrixXd.size(); ++tmp) {
        *tmp = matrixXd.data() + shift;
        multiplicationLine = **tmp;
        for (int shift_row = 1; shift_row < rows; ++shift_row) {
            ++*tmp;
            multiplicationLine *= **tmp;
        }
        shift += rows;
        sum += multiplicationLine;
    }

    delete[] arrayPtr;

    return sum;
}

double sumPowElemVector(const Eigen::MatrixXd &matrixXd) {
    auto *begin = matrixXd.data();
    auto *end = matrixXd.data() + matrixXd.size();
    double sum = 0.0;

    for (; begin != end; ++begin) {
        sum += std::pow(*begin, 2);
    }

    return sum;
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

#if not defined(MANUAL)
    /*
     * нормализуем показатели
     * нужно чтобы корректно выставить коэффициент и крутить линии регрессии относительно оси асцисс (чтобы не уползать в бесконечность)
     * https://neuronus.com/theory/nn/925-sposoby-normalizatsii-peremennykh.html
     */
    Eigen::VectorXd X_norm(csvTransform.NormalizeVectorXd(X));
#endif

    double SS_tot = 0.0;
    {
        auto *begin = y.data();
        auto *end = y.data() + y.size();
        for (; begin != end; ++begin) {
            SS_tot += std::pow(*begin - y.mean(), 2);
        }
        SS_tot /= y.size();
    }

    /*
    * slope -      угловой коэффициент (множитель регрессора, определяющий скорость роста целевой переменной
    *              относительно регрессора)
    *              представляет собой величину, на которую Y увеличивается в среднем, если мы увеличиваем X
    *              на одну единицу.
    * intercept -  точка пересечения оси абцисс
    */

    double slope_normalize = 0.0, intercept = 0.0, slope = 0.0;

#if defined(MANUAL)
    double sum_multipl = sumMultiplication(dataMatrix);
    double count_elem = X.size();
    double sum_pow = sumPowElemVector(X);

    //https://www.matematicus.ru/matematicheskaya-statistika/metod-naimenshih-kvadratov-regressiya
    for (int i = 0; i < 100000; ++i) {
        slope_normalize = (count_elem * sum_multipl - X.sum() * y.sum()) /
                                                                (count_elem * sum_pow - std::pow(X.sum(), 2));
        slope_normalize -= 0.001 * slope_normalize;
        intercept = (y.sum() - slope_normalize * X.sum()) / count_elem;
        intercept -= 0.001 * intercept;
    }

    slope = slope_normalize;
#else
    double count_elem = X.size();
    double learningRate = 0.001;
    double *begin_x = nullptr;
    double *end_x = nullptr;
    double *begin_y = nullptr;
    double sum_slope = 0.0;
    double sum_intercept = 0.0;

    for (int i = 0; i < 100000; ++i) {
        sum_slope = 0.0;
        sum_intercept = 0.0;

        for (begin_x = X_norm.data(),
             end_x = X_norm.data() + X_norm.size(),
             begin_y = y.data();
             begin_x != end_x;
             ++begin_x,
                     ++begin_y) {
            sum_intercept += intercept + (slope_normalize * *begin_x) - *begin_y;
            sum_slope += sum_intercept * *begin_x;
        }

        slope_normalize -= learningRate * (sum_slope / count_elem);
        intercept -= learningRate * (sum_intercept / count_elem);
    }

    slope = slope_normalize / X.maxCoeff();
#endif


#if defined(PRINT_MODE)
    {
        std::cout << "VectorXd X:" << "\n";

        auto *begin = X.data();
        auto *end = X.data() + X.size();
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << "\n\n";
    }

    {
        std::cout << "VectorXd y:" << "\n";

        auto *begin = y.data();
        auto *end = y.data() + y.size();
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << "\n\n";
    }

    {
        std::cout << "VectorXd X_norm:" << "\n";

        auto *begin = X_norm.data();
        auto *end = X_norm.data() + X_norm.size();
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << "\n\n";
    }

    {
        std::cout << "SS_tot: " << SS_tot << "\n";
    }
#endif

    std::cout << "intercept (theta0): " << intercept << "\n"
              << "    slope (theta1): " << slope << "\n";

    std::fstream file_to_safe("../../resources/coefficient.txt");

    file_to_safe << std::fixed << intercept << " " << slope;
    file_to_safe.close();

    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

