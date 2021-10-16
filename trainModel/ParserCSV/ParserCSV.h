#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <fstream>
#include <vector>

/*
 * converts csv to 2d vector by separator
 */
template<typename T>
class ParserCSV {
private:
    std::ifstream               csv_file_;
    std::vector<std::vector<T>> two_d_array_;
    std::vector<std::string>    first_line_;
    char                        separator_;
    size_t                      count_column_;
    size_t                      count_row_;

public:
    ParserCSV() = delete;
    ParserCSV(const ParserCSV&) = delete;
    ParserCSV(const char *pathToCSV, char separator) : csv_file_(pathToCSV), separator_(separator) {
        if (csv_file_.is_open()) {
            std::vector<std::string> lines;
            std::string line;
            // read from csv
            while (std::getline(csv_file_, line)) {
                lines.push_back(line);
            }
            count_column_ = lines.size();
            size_t current_pos = 0, pos_next = lines[0].find(separator_);
            // save the first line
            first_line_.push_back(lines[0].substr(current_pos, pos_next));
            for (;  pos_next != std::string::npos;  pos_next = lines[0].find(separator_, current_pos),
                    current_pos = pos_next + 1,
                    ++count_row_) {
                first_line_.push_back(lines[0].substr(current_pos, pos_next));
            }
            // save next lines
            for (size_t i = 1; i < lines.size(); ++i) {
                std::vector<T> tmp;
                current_pos = 0;
                pos_next = lines[i].find(separator_);
                for (;pos_next != std::string::npos; pos_next = lines[i].find(separator_, current_pos)) {
                    tmp.push_back(std::stod(lines[i].substr(current_pos, pos_next)));
                    current_pos = pos_next + 1;
                }
                tmp.push_back(std::stod(lines[i].substr(current_pos, pos_next)));
                two_d_array_.push_back(tmp);
            }
        }
    };

    ParserCSV& operator=(const ParserCSV&) = delete;

    size_t getCountColumn() const {
        return count_column_;
    }

    size_t getCountRow() const {
        return count_row_;
    }

    /*
     * it is not protected from going beyond the memory area
     */
    const std::vector<T> &getRow(size_t i) const {
        return two_d_array_[i];
    }

    const std::vector<std::string> &getFirstLine() const {
        return first_line_;
    }

    const std::vector<std::vector<T>> &getTwoDArray() const {
        return two_d_array_;
    }

    virtual ~ParserCSV() {
    };
};



#endif //PARSERCSV_H

//
// Created by Arclight Natashia on 8/27/21.
//