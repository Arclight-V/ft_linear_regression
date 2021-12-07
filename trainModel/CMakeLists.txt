cmake_minimum_required(VERSION 3.20)
project(trainModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Warray-bounds -O2")
add_executable(trainModel trainModel.cpp ParserCSV/ParserCSV.h CSVTransform/CSVTransform.cpp CSVTransform/CSVTransform.h)