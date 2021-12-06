#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>
#include <ostream>
#include <iostream>


template<typename T>
class ParserCSV {
private:
    ParserCSV() {};
    std::ifstream csvFile_;
    std::string header_;
    std::vector<std::vector<T>> rows_;
    std::vector<std::vector<T>> columns_;

public:
    ParserCSV(const char *pathToCSV, char delimiter) : csvFile_(pathToCSV) {
        if (csvFile_.is_open()) {
            std::vector<std::string> vector_strings;
            std::cout << vector_strings.capacity();
            std::string line;

            std::getline(csvFile_, header_);

            while (std::getline(csvFile_, line)) {
                vector_strings.push_back(line);
            }

            for (size_t i = 0; i < vector_strings.size(); ++i) {
                std::vector<T> to_add;
                size_t last = 0, next = 0;
                while ((next = vector_strings[i].find(delimiter, last)) != std::string::npos) {
                    to_add.push_back(
                            std::stod(
                                    vector_strings[i].substr(last, next - last)
                                    )
                                    );
                    last = next + 1;
                }
                to_add.push_back(
                        std::stod(
                                vector_strings[i].substr(last, next - last)
                                )
                                );
                rows_.push_back(to_add);
            }

            for (size_t i = 0; i < rows_[0].size(); ++i) {
                std::vector<T> to_add;
                for (size_t j = 0; j < rows_.size(); ++j) {
                    to_add.push_back(rows_[j][i]);
                    std::cout << rows_[j][i] << "\n";
                }
                columns_.push_back(to_add);
            }
        }
    };

    virtual ~ParserCSV() {};
};


#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//