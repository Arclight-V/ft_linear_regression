#include "ParserCSV/ParserCSV.h"
#include "iostream"

int main() {
    ParserCSV<double> parserCsv("../../resources/data.csv", ',');

    const std::string column_name_km = "km";
    const std::string column_name_prise = "price";

    std::vector X(parserCsv.getColumns(column_name_km));
    std::vector y(parserCsv.getColumns(column_name_prise));

    std::sort(X.begin(), X.end());
    std::sort(y.begin(), y.end());

    /*
     * нормализуем показатели
     * нужно чтобы корректно выставить коэффициент и крутить линии регрессии относительно оси асцисс (чтобы не уползать в бесконечность)
     * https://neuronus.com/theory/nn/925-sposoby-normalizatsii-peremennykh.html
     */

    auto X_min = X[0];
    auto X_max = X[X.size() - 1];

    std::vector<double> X_norm(X.size());

    for (size_t i = 0; i < X.size(); ++i) {
        X_norm[i] = (X[i] - X_min) / (X_max - X_min);
    }

    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

