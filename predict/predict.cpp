#include <iostream>
#include <fstream>


int main() {
    double          theta0 = 0.0, theta1 = 0.0, millage = 0.0;
    std::string     line;
    std::ifstream   in("../../resources/coefficient.txt");
    if (in.is_open()) {
        std::getline(in,line);
        theta0 = std::stod(line);
        theta1 = std::stod(line.substr(line.find(' '), line.size()));
    } else {
        std::cout << "File opening error\n";
        return -1;
    }

    std::cout << "Enter the positive mileage of the car: \n";
    std::getline(std::cin, line);
    try {
        millage = std::stod(line);
    } catch (std::invalid_argument) {
        std::cout << "No conversion could be performed\n";
        return -1;
    } catch (std::out_of_range) {
        std::cout << "The converted value would fall out of the range of the result type or if the underlying function\n";
        return -1;
    }
    if (millage < 0) {
        std::cout << "The mileage must be a positive number\n";
        return -1;
    }

    std::cout << "Expected cost according to the model: " << std::fixed << theta0 + theta1 * millage << '\n';
}

//
// Created by Arclight Natashia on 8/27/21.
//

