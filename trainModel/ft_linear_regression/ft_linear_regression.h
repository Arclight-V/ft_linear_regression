//
// Created by Anatashi on 09.12.2021.
//

#ifndef FT_LINEAR_REGRESSION_FT_LINEAR_REGRESSION_H
#define FT_LINEAR_REGRESSION_FT_LINEAR_REGRESSION_H

#include <Eigen/Dense>

class ft_linear_regression {
private:
    /*
    * slope -      угловой коэффициент (множитель регрессора, определяющий скорость роста целевой переменной
    *              относительно регрессора)
    *              представляет собой величину, на которую Y увеличивается в среднем, если мы увеличиваем X
    *              на одну единицу.
    * intercept -  точка пересечения оси абцисс
    */
    double intercept_ = 0.0;
    double slope_ = 0.0;

public:
    ft_linear_regression() = default;
    ft_linear_regression(const ft_linear_regression& rhs) = delete;
    ~ft_linear_regression() = default;
    ft_linear_regression& operator=(const ft_linear_regression& rhs) = delete;

    /*
     * X - Training data (данные обучения)
     * y - Target values (целевые значения)
     */
    void fit_subject(const Eigen::VectorXd& X,
                     const Eigen::VectorXd& y,
                     double learning_rate=0.001,
                     size_t iteration=100000);

    void fit(Eigen::MatrixXd& dataMatrix);
    double sumPowElemVector(const Eigen::MatrixXd &matrixXd);
    double sumMultiplication(const Eigen::MatrixXd &matrixXd);

    double getIntercept() const;
    double getSlope() const;

};


#endif //FT_LINEAR_REGRESSION_FT_LINEAR_REGRESSION_H
