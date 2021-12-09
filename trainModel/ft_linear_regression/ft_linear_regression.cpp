//
// Created by OUT-Kalanchin-VV on 09.12.2021.
//

#include "ft_linear_regression.h"

void ft_linear_regression::fit_subject(const Eigen::VectorXd& X,
                                       const Eigen::VectorXd& y,
                                       double learning_rate,
                                       size_t iteration) {
    double intercept = 0.0;
    double slope_normalize = 0.0;
    double count_elem = X.size();
    const double *begin_x = nullptr;
    const double *end_x = nullptr;
    const double *begin_y = nullptr;
    double sum_slope = 0.0;
    double sum_intercept = 0.0;

    for (size_t i = 0; i < iteration; ++i) {
        sum_slope = 0.0;
        sum_intercept = 0.0;

        for (begin_x = X.data(),
             end_x = X.data() + X.size(),
             begin_y = y.data();
             begin_x != end_x;
             ++begin_x,
                     ++begin_y) {
            sum_intercept += intercept + (slope_normalize * *begin_x) - *begin_y;
            sum_slope += sum_intercept * *begin_x;
        }

        slope_normalize -= learning_rate * (sum_slope / count_elem);
        intercept -= learning_rate * (sum_intercept / count_elem);
    }

    slope_ = slope_normalize / X.maxCoeff();
    intercept_ = intercept;
}

// the sum of the multiplication of elements
double ft_linear_regression::sumMultiplication(const Eigen::MatrixXd &matrixXd) {
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

double ft_linear_regression::sumPowElemVector(const Eigen::MatrixXd &matrixXd) {
    auto *begin = matrixXd.data();
    auto *end = matrixXd.data() + matrixXd.size();
    double sum = 0.0;

    for (; begin != end; ++begin) {
        sum += std::pow(*begin, 2);
    }

    return sum;
}

double ft_linear_regression::getIntercept() const {
    return intercept_;
}

double ft_linear_regression::getSlope() const {
    return slope_;
}
