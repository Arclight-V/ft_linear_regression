cmake_minimum_required(VERSION 3.20)
project(trainModel)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress -Warray-bounds -O2")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Waddress")
find_package(Boost 1.76.0)
find_package(Eigen3 3.4)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
#add_compile_definitions(PRINT_MODE)
#add_compile_definitions(SUBJECT)
add_executable(trainModel trainModel.cpp CSVTransform/CSVTransform.cpp CSVTransform/CSVTransform.h ft_linear_regression/ft_linear_regression.cpp ft_linear_regression/ft_linear_regression.h)

