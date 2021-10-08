cmake_minimum_required(VERSION 3.20)
project(trainModel)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_executable(trainModel trainModel.cpp ParserCSV/ParserCSV.h)
target_link_libraries(trainModel Eigen3::Eigen)