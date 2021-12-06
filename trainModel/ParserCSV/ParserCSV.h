#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>
#include <map>
#include <ostream>
#include <iostream>


template<typename T>
class ParserCSV {

private:
    using Vec = std::vector<T>;
    using TwoDArray = std::vector<Vec>;
    using VecStrings = std::vector<std::string>;
    using СolumnMap = std::map<std::string, Vec>;

    std::ifstream   csvFile_;
    VecStrings      header_;
    TwoDArray       vectorRows_;
    TwoDArray       vectorColumns_;
    СolumnMap       columnMap_;

    void create_rows(VecStrings & vector_strings,
                   char delimiter,
                   TwoDArray& array) {
        for (size_t i = 0; i < vector_strings.size(); ++i) {
            Vec to_add;
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
            array.push_back(to_add);
        }
    }

    void create_columns() {
        for (size_t i = 0; i < vectorRows_[0].size(); ++i) {
            Vec to_add;
            for (size_t j = 0; j < vectorRows_.size(); ++j) {
                to_add.push_back(vectorRows_[j][i]);
            }
            vectorColumns_.push_back(to_add);
        }
    }

    void create_headers(std::string& line, char delimiter) {
            size_t last = 0, next = 0;
            while ((next = line.find(delimiter, last)) != std::string::npos) {
                header_.push_back(
                                line.substr(last, next - last)
                                );
                last = next + 1;
            }
            header_.push_back(
                            line.substr(last, next - last)
                            );
    }

    void create_column_map() {
        for (size_t i = 0; i < header_.size(); ++i) {
            columnMap_.insert(std::make_pair(header_[i], vectorColumns_[i]));
        }
    }

public:
    ParserCSV() = delete;
    ParserCSV(const char *pathToCSV, char delimiter) : csvFile_(pathToCSV) {
        if (csvFile_.is_open()) {
            VecStrings headers;
            VecStrings lines;
            std::string line;

            std::getline(csvFile_, line);
            headers.push_back(line);
            create_headers(line, delimiter);

            while (std::getline(csvFile_, line)) {
                lines.push_back(line);
            }

            create_rows(lines, delimiter, vectorRows_);
            create_columns();
            create_column_map();

        }
    }

    const TwoDArray &getVectorRows() const {
        return vectorRows_;
    }

    const TwoDArray &getVectorColumns() const {
        return vectorColumns_;
    };

    const Vec &getColumns(const std::string& column_name) {
        return columnMap_.at(column_name);
    }

    virtual ~ParserCSV() {};
};


#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//