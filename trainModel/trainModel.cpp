#include "ParserCSV/ParserCSV.h"
#include "CSVTransform/CSVTransform.h"
#include "iostream"

namespace csv_parameters {
    std::string kCSVFileName = "../../resources/data.csv";
    std::string kDelimiter = ",";
    constexpr bool kHeader = true;
} // csv_parameters

int main() {

//    ParserCSV<double> parserCsv("../../resources/data.csv", ',');
//
//    const std::string column_name_km = "km";
//    const std::string column_name_prise = "price";
//
//    /*
//     * X -  значения фактора (регрессора) она же независимоя переменная или предикат
//     * y -  фактическое значение целевой переменной при этом регрессоре она же зависимая переменная
//     *      или переменная отклика
//     */
//    std::vector X(parserCsv.getColumns(column_name_km));
//    std::vector y(parserCsv.getColumns(column_name_prise));
//
//    std::sort(X.begin(), X.end());
//    std::sort(y.begin(), y.end());
//
//    /*
//     * нормализуем показатели
//     * нужно чтобы корректно выставить коэффициент и крутить линии регрессии относительно оси асцисс (чтобы не уползать в бесконечность)
//     * https://neuronus.com/theory/nn/925-sposoby-normalizatsii-peremennykh.html
//     */
//
//    auto X_min = X[0];
//    auto X_max = X[X.size() - 1];
//
//    std::vector<double> X_norm(X.size());
//
//    for (size_t i = 0; i < X.size(); ++i) {
//        X_norm[i] = (X[i] - X_min) / (X_max - X_min);
//    }
//
//    /*
//     * slope -      угловой коэффициент (множитель регрессора, определяющий скорость роста целевой переменной
//     *              относительно регрессора)
//     *              представляет собой величину, на которую Y увеличивается в среднем, если мы увеличиваем X
//     *              на одну единицу.
//     * intercept -  точка пересечения оси абцисс
//     */
//
//    float slope_normalize = 0.0, intercept = 0.0;

    CSVTransform csvTransform(csv_parameters::kCSVFileName,
                              csv_parameters::kDelimiter,
                              csv_parameters::kHeader);
    std::vector<std::vector<std::string>> dataset(csvTransform.readCSV());

    int rows = dataset.size();
    int columns = dataset[0].size();

    Eigen::MatrixXd dataMatrix = csvTransform.CSVtoEigenMatrixXd(dataset, rows, columns);

    std::cout << dataMatrix << '\n';



    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

