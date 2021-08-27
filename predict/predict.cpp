#include <iostream>
#include <fstream>


int main() {
    double          theta0 = 0.0, theta1 = 0.0;
    std::string     line;
    std::ifstream   in("../../coefficient.txt");
    if (in.is_open()) {
        std::getline(in,line);
        theta0 = std::stod(line);
        theta1 = std::stod(line.substr(line.find(' '), line.size()));
        std::cout << theta0 << " " << theta1 << '\n';
    } else {
        std::cout << "File opening error\n";
        return -1;
    }
}

//
// Created by Arclight Natashia on 8/27/21.
//

