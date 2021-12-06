#include "ParserCSV/ParserCSV.h"
#include "iostream"

int main() {
    ParserCSV<double> parserCsv("../../resources/data.csv", ',');

    const std::string column_name_km = "km";
    const std::string column_name_prise = "price";

    std::vector X(parserCsv.getColumns(column_name_km));
    std::vector y(parserCsv.getColumns(column_name_prise));

    return 0;
}

//
// Created by Arclight Natashia on 8/27/21.
//

