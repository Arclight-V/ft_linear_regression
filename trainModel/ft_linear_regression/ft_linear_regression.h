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


    /*
     * нормализуем показатели
     * нужно чтобы корректно выставить коэффициент и крутить линии регрессии относительно оси асцисс (чтобы не уползать в бесконечность)
     * https://neuronus.com/theory/nn/925-sposoby-normalizatsii-peremennykh.html
     */
    void NormalizeVectorXd(Eigen::VectorXd& vectorXd);

    double sumPowElemVector(const Eigen::MatrixXd &matrixXd);
    double sumMultiplication(const Eigen::MatrixXd &matrixXd);

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

    /*
     * dataMatrix
     * row_0 - Training data (данные обучения)
     * row_1 - Target values (целевые значения)
     */
    void fit(Eigen::MatrixXd& dataMatrix,
             double learning_rate=0.001,
             size_t iteration=100000);

    Eigen::VectorXd predict(const Eigen::VectorXd& X);

    /*
     * X - Test samples.
     * y - True values for X
     * https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D1%8D%D1%84%D1%84%D0%B8%D1%86%D0%B8%D0%B5%D0%BD%D1%82_%D0%B4%D0%B5%D1%82%D0%B5%D1%80%D0%BC%D0%B8%D0%BD%D0%B0%D1%86%D0%B8%D0%B8
     */
    double score(const Eigen::VectorXd& X, const Eigen::VectorXd& y);

    double getIntercept() const;
    double getSlope() const;
};


#endif //FT_LINEAR_REGRESSION_FT_LINEAR_REGRESSION_H
