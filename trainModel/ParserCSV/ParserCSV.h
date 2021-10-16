#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>


template<typename T>
class ParserCSV {
private:
    std::ifstream               csv_file_;
    std::vector<std::vector<T>> array_numbers_;
    std::vector<std::string>    first_line_;

public:
    ParserCSV() = delete;
    ParserCSV(const ParserCSV&) = delete;
    ParserCSV(const char *pathToCSV) : csv_file_(pathToCSV), array_numbers_() {
        if (csv_file_.is_open()) {
            std::vector<std::string> lines;
            std::string line;
            // read from csv
            while (std::getline(csv_file_, line)) {
                lines.push_back(line);
            }
            size_t current_pos = 0, pos_next = lines[0].find( ',');
            // save the first line
            for (; pos_next != std::string::npos; pos_next = lines[0].find(',', current_pos)) {
                first_line_.push_back(lines[0].substr(current_pos, pos_next));
                current_pos = pos_next + 1;
            }
            first_line_.push_back(lines[0].substr(current_pos, pos_next));
            // save next lines
            for (size_t i = 1; i < lines.size(); ++i) {
                std::vector<T> tmp;
                current_pos = 0;
                pos_next = lines[i].find( ',');
                for (;pos_next != std::string::npos; pos_next = lines[i].find(',', current_pos)) {
                    tmp.push_back(std::stod(lines[i].substr(current_pos, pos_next)));
                    current_pos = pos_next + 1;
                }
                tmp.push_back(std::stod(lines[i].substr(current_pos, pos_next)));
                array_numbers_.push_back(tmp);
            }
        }
    };

    ParserCSV& operator=(const ParserCSV&) = delete;

    virtual ~ParserCSV() {
    };
};



#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//