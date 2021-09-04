cmake_minimum_required(VERSION 3.20)
project(trainModel)

set(CMAKE_CXX_STANDARD 20)

add_executable(trainModel trainModel.cpp ParserCSV/ParserCSV.h)