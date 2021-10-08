#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

int main() {

    typedef float DType;
    using Matrix = Eigen::Matrix<DType, Eigen::Dynamic, Eigen::Dynamic>;
    int n = 10000;
    Matrix x(n,1);
    Matrix y(n,1);

    Eigen::LeastSquaresConjugateGradient<Matrix> gd;
    gd.setMaxIterations(1000);
    gd.setTolerance(0.001) ;
    gd.compute(x);
    auto b = gd.solve(y);

//    Eigen::MatrixXf new_x(5, 2);
//    new_x << 1, 1, 1, 2, 1, 3, 1, 4, 1, 5;
////    auto new_y = new_x.array().rowwise() * b.transpose().array();
//
//    auto b = (x.transpose() * x).ldlt().solve(x.transpose() * y);

    return 0;
}
