//
// Created by OUT-Kalanchin-VV on 09.12.2021.
//

#include "ft_linear_regression.h"

void ft_linear_regression::NormalizeVectorXd(Eigen::VectorXd &vectorXd) {
    double max = vectorXd.maxCoeff();
    double min = vectorXd.minCoeff();
    auto *begin = vectorXd.data();
    auto *end = vectorXd.data() + vectorXd.size();

    for (; begin != end; ++begin) {
        *begin = (*begin - min) / (max - min);
    }
}

void ft_linear_regression::fit_subject(const Eigen::VectorXd& X,
                                       const Eigen::VectorXd& y,
                                       double learning_rate,
                                       size_t iteration) {
    Eigen::VectorXd X_norm(X);
    NormalizeVectorXd(X_norm);
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

        for (begin_x = X_norm.data(),
             end_x = X_norm.data() + X_norm.size(),
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

void ft_linear_regression::fit(Eigen::MatrixXd& dataMatrix,
                               double learning_rate,
                               size_t iteration) {
    Eigen::VectorXd X(dataMatrix.row(0));
    Eigen::VectorXd y(dataMatrix.row(1));
    double sum_multipl = sumMultiplication(dataMatrix);
    double count_elem = X.size();
    double sum_pow = sumPowElemVector(X);
    double slope_normalize = 0.0;
    double intercept = 0.0;

    //https://www.matematicus.ru/matematicheskaya-statistika/metod-naimenshih-kvadratov-regressiya
    for (size_t i = 0; i < iteration; ++i) {
        slope_normalize = (count_elem * sum_multipl - X.sum() * y.sum()) /
                          (count_elem * sum_pow - std::pow(X.sum(), 2));
        slope_normalize -= learning_rate * slope_normalize;
        intercept = (y.sum() - slope_normalize * X.sum()) / count_elem;
        intercept -= learning_rate * intercept;
    }

    slope_ = slope_normalize;
    intercept_ = intercept;
}

Eigen::VectorXd ft_linear_regression::predict(const Eigen::VectorXd& X) {
    Eigen::VectorXd vectorXd(X);

    auto *begin = vectorXd.data();
    auto *end = vectorXd.data() + vectorXd.size();

    for (; begin != end; ++begin) {
        *begin = intercept_ + slope_ * *begin;
    }

    return vectorXd;
}

double ft_linear_regression::score(const Eigen::VectorXd& X, const Eigen::VectorXd& y)  {

    // найдем сумму квадратов остатков регрессии
    double SS_res = 0.0;
    auto* begin_X = X.data();
    auto* end_X = X.data() + X.size();
    auto* begin_y = y.data();
    auto* end_y = y.data() + y.size();

    for (; begin_X != end_X; ++begin_X, ++begin_y) {
        SS_res += std::pow(*begin_X - *begin_y, 2);
    }
    SS_res /= X.size();

    // SS_tor - общая сумма квадратов (квадраты отклонений объясняемой переменной от среднего значения)
    double SS_tor = 0.0;

    for (begin_y = y.data(); begin_y != end_y; ++begin_y) {
        SS_tor += std::pow(*begin_y - y.mean(), 2);
    }
    SS_tor /= y.size();

    // коэффициент детерминации
    return 1 - SS_res / SS_tor;
}

double ft_linear_regression::getIntercept() const {
    return intercept_;
}

double ft_linear_regression::getSlope() const {
    return slope_;
}
